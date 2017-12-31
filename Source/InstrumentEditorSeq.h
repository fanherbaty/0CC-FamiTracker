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


#pragma once

#include "InstrumentEditPanel.h"		// // //

class CInstrument;		// // //
enum inst_type_t : int;		// // //

/*!
	\brief Specialization of the instrument sequence editor panel class for CSeqInstrument.
*/
class CInstrumentEditorSeq : public CSequenceInstrumentEditPanel
{
	DECLARE_DYNAMIC(CInstrumentEditorSeq)

public:
	CInstrumentEditorSeq(CWnd* pParent, LPCTSTR Title, const LPCTSTR *SeqName, int Vol, int Duty, inst_type_t Type);
	int GetIDD() const override { return IDD; }
	LPCTSTR GetTitle() const override { return m_pTitle; }

	// Public
	virtual void SelectInstrument(std::shared_ptr<CInstrument> pInst);
	void UpdateSequenceString(bool Changed) override;		// // //

// Dialog Data
	enum { IDD = IDD_INSTRUMENT_INTERNAL };

protected:
	virtual void OnKeyReturn();

	void SelectSequence(int Sequence, int Type);
	void SetupParser() const override;		// // //

protected:
	const LPCTSTR *m_pSequenceName;
	LPCTSTR m_pTitle;
	const int m_iMaxVolume;
	const int m_iMaxDuty;
	const inst_type_t m_iInstType;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedInstsettings(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeSeqIndex();
	afx_msg void OnBnClickedFreeSeq();
	virtual BOOL DestroyWindow();
	afx_msg void OnCloneSequence();
};
