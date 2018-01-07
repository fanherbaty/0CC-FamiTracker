/*
** FamiTracker - NES/Famicom sound tracker
** Copyright (C) 2005-2014  Jonathan Liss
**
** 0CC-FamiTracker is (C) 2014-2018 HertzDevil
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
** Library General Public License for more details.  To obtain a
** copy of the GNU Library General Public License, write to the Free
** Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
**
** Any permitted reproduction of these routines, in whole or in part,
** must bear this legend.
*/

#include "InstrumentN163.h"		// // //
#include "ModuleException.h"		// // //
#include "DocumentFile.h"
#include "SimpleFile.h"

// // // Default wave
static const char TRIANGLE_WAVE[] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
};
static const int DEFAULT_WAVE_SIZE = std::size(TRIANGLE_WAVE);

const char *const CInstrumentN163::SEQUENCE_NAME[] = {"Volume", "Arpeggio", "Pitch", "Hi-pitch", "Wave Index"};

CInstrumentN163::CInstrumentN163() : CSeqInstrument(INST_N163),		// // //
	m_iSamples(),
	m_iWaveSize(DEFAULT_WAVE_SIZE),
	m_iWavePos(0),
	m_bAutoWavePos(false),		// // // 050B
	m_iWaveCount(1)
{
	for (int j = 0; j < DEFAULT_WAVE_SIZE; ++j)
		m_iSamples[0][j] = TRIANGLE_WAVE[j];
}

std::unique_ptr<CInstrument> CInstrumentN163::Clone() const
{
	auto inst = std::make_unique<std::decay_t<decltype(*this)>>();		// // //
	inst->CloneFrom(this);
	return inst;
}

void CInstrumentN163::CloneFrom(const CInstrument *pInst)
{
	CSeqInstrument::CloneFrom(pInst);

	if (auto pNew = dynamic_cast<const CInstrumentN163*>(pInst)) {
		SetWaveSize(pNew->GetWaveSize());
		SetWavePos(pNew->GetWavePos());
	//	SetAutoWavePos(pInst->GetAutoWavePos());
		SetWaveCount(pNew->GetWaveCount());

		for (int i = 0; i < MAX_WAVE_COUNT; ++i)
			for (int j = 0; j < MAX_WAVE_SIZE; ++j)
				SetSample(i, j, pNew->GetSample(i, j));
	}
}

void CInstrumentN163::Store(CDocumentFile *pDocFile) const
{
	// Store sequences
	CSeqInstrument::Store(pDocFile);		// // //

	// Store wave
	pDocFile->WriteBlockInt(m_iWaveSize);
	pDocFile->WriteBlockInt(m_iWavePos);
	//pDocFile->WriteBlockInt(m_bAutoWavePos ? 1 : 0);
	pDocFile->WriteBlockInt(m_iWaveCount);

	for (int i = 0; i < m_iWaveCount; ++i) {
		for (int j = 0; j < m_iWaveSize; ++j) {
			pDocFile->WriteBlockChar(m_iSamples[i][j]);
		}
	}
}

bool CInstrumentN163::Load(CDocumentFile *pDocFile)
{
	if (!CSeqInstrument::Load(pDocFile)) return false;		// // //

	m_iWaveSize = CModuleException::AssertRangeFmt(pDocFile->GetBlockInt(), 4, MAX_WAVE_SIZE, "N163 wave size");
	m_iWavePos = CModuleException::AssertRangeFmt(pDocFile->GetBlockInt(), 0, MAX_WAVE_SIZE - 1, "N163 wave position");
	CModuleException::AssertRangeFmt<MODULE_ERROR_OFFICIAL>(m_iWavePos, 0, 0x7F, "N163 wave position");
	if (pDocFile->GetBlockVersion() >= 8) {		// // // 050B
		bool AutoPosition = pDocFile->GetBlockInt() != 0;
	}
	m_iWaveCount = CModuleException::AssertRangeFmt(pDocFile->GetBlockInt(), 1, MAX_WAVE_COUNT, "N163 wave count");
	CModuleException::AssertRangeFmt<MODULE_ERROR_OFFICIAL>(m_iWaveCount, 1, 0x10, "N163 wave count");

	for (int i = 0; i < m_iWaveCount; ++i) {
		for (int j = 0; j < m_iWaveSize; ++j) try {
			m_iSamples[i][j] = CModuleException::AssertRangeFmt(pDocFile->GetBlockChar(), 0, 15, "N163 wave sample");
		}
		catch (CModuleException e) {
			e.AppendError("At wave %i, sample %i,", i, j);
			throw e;
		}
	}

	return true;
}

void CInstrumentN163::DoSaveFTI(CSimpleFile &File) const
{
	// Sequences
	CSeqInstrument::DoSaveFTI(File);		// // //

	// Write wave config
	int WaveCount = GetWaveCount();
	int WaveSize = GetWaveSize();

	File.WriteInt(WaveSize);
	File.WriteInt(GetWavePos());
//	File.WriteInt(m_bAutoWavePos);		// // // 050B
	File.WriteInt(WaveCount);

	for (int i = 0; i < WaveCount; ++i) {
		for (int j = 0; j < WaveSize; ++j) {
			File.WriteChar(GetSample(i, j));
		}
	}
}

void CInstrumentN163::DoLoadFTI(CSimpleFile &File, int iVersion)
{
	// Sequences
	CSeqInstrument::DoLoadFTI(File, iVersion);		// // //

	// Read wave config
	int WaveSize = CModuleException::AssertRangeFmt(static_cast<int>(File.ReadInt()), 4, MAX_WAVE_SIZE, "N163 wave size");
	int WavePos = CModuleException::AssertRangeFmt(static_cast<int>(File.ReadInt()), 0, MAX_WAVE_SIZE - 1, "N163 wave position");
	if (iVersion >= 25) {		// // // 050B
		m_bAutoWavePos = File.ReadInt() != 0;
	}
	int WaveCount = CModuleException::AssertRangeFmt(static_cast<int>(File.ReadInt()), 1, MAX_WAVE_COUNT, "N163 wave count");

	SetWaveSize(WaveSize);
	SetWavePos(WavePos);
	SetWaveCount(WaveCount);

	for (int i = 0; i < WaveCount; ++i)
		for (int j = 0; j < WaveSize; ++j) try {
			SetSample(i, j, CModuleException::AssertRangeFmt(File.ReadChar(), 0, 15, "N163 wave sample"));
		}
	catch (CModuleException e) {
		e.AppendError("At wave %i, sample %i,", i, j);
		throw e;
	}
}

bool CInstrumentN163::IsWaveEqual(const CInstrumentN163 &Instrument) const {		// // //
	int Count = GetWaveCount();
	int Size = GetWaveSize();

	if (Instrument.GetWaveCount() != Count)
		return false;

	if (Instrument.GetWaveSize() != Size)
		return false;

	for (int i = 0; i < Count; ++i) {
		for (int j = 0; j < Size; ++j) {
			if (GetSample(i, j) != Instrument.GetSample(i, j))
				return false;
		}
	}

	return true;
}

bool CInstrumentN163::InsertNewWave(int Index)		// // //
{
	if (m_iWaveCount >= CInstrumentN163::MAX_WAVE_COUNT)
		return false;
	if (Index < 0 || Index > m_iWaveCount || Index >= CInstrumentN163::MAX_WAVE_COUNT)
		return false;

	memmove(m_iSamples[Index + 1], m_iSamples[Index], CInstrumentN163::MAX_WAVE_SIZE * (m_iWaveCount - Index) * sizeof(int));
	memset(m_iSamples[Index], 0, CInstrumentN163::MAX_WAVE_SIZE * sizeof(int));
	m_iWaveCount++;
	InstrumentChanged();
	return true;
}

bool CInstrumentN163::RemoveWave(int Index)		// // //
{
	if (m_iWaveCount <= 1)
		return false;
	if (Index < 0 || Index >= m_iWaveCount)
		return false;

	memmove(m_iSamples[Index], m_iSamples[Index + 1], CInstrumentN163::MAX_WAVE_SIZE * (m_iWaveCount - Index - 1) * sizeof(int));
	m_iWaveCount--;
	InstrumentChanged();
	return true;
}

int CInstrumentN163::GetWaveSize() const
{
	return m_iWaveSize;
}

void CInstrumentN163::SetWaveSize(int size)
{
	m_iWaveSize = size;
	InstrumentChanged();
}

int CInstrumentN163::GetSample(int wave, int pos) const
{
	return m_iSamples[wave][pos];
}

void CInstrumentN163::SetSample(int wave, int pos, int sample)
{
	m_iSamples[wave][pos] = sample;
	InstrumentChanged();
}

int CInstrumentN163::GetWavePos() const
{
	return m_iWavePos;
}

void CInstrumentN163::SetWavePos(int pos)
{
	m_iWavePos = MAX_WAVE_SIZE - m_iWaveSize;		// // // prevent reading non-wave n163 registers
	if (pos < m_iWavePos) m_iWavePos = pos;
	InstrumentChanged();
}
/*
void CInstrumentN163::SetAutoWavePos(bool Enable)
{
	m_bAutoWavePos = Enable;
}

bool CInstrumentN106::GetAutoWavePos() const
{
	return m_bAutoWavePos;
}
*/
void CInstrumentN163::SetWaveCount(int count)
{
	ASSERT(count <= MAX_WAVE_COUNT);
	if (m_iWaveCount != count)			// // //
		InstrumentChanged();
	m_iWaveCount = count;
}

int CInstrumentN163::GetWaveCount() const
{
	return m_iWaveCount;
}
