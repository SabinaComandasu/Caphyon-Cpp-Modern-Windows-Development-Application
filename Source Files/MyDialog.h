#pragma once

#include "afxwin.h"
#include "afxdialogex.h"

class MyDialog : public CDialogEx
{
    DECLARE_DYNAMIC(MyDialog)

public:
    MyDialog(CWnd* pParent = nullptr);   // Standard constructor
    virtual ~MyDialog();

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG1 };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
    afx_msg void OnLbnSelchangeActionList();
    DECLARE_MESSAGE_MAP()

private:
    CEdit Edit;   // Existing text box for file path
    CButton Browse;    // Button for browsing files
    CButton Cancel;
    CButton OK;
    CEdit OutputEdit;
    CStatic Logo;
    CListBox ActionList;

    PROCESS_INFORMATION pi;
    HANDLE hChildStdoutRd;
    HANDLE hChildStdoutWr;

public:
    afx_msg void OnEnChangeEdit1();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedOk();
    afx_msg void OnEnChangeEdit2();
    void MyDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnCbnSelchangeCombo1();
    afx_msg void OnBnClickedBrowse();  
    afx_msg void OnStnClickedLogo();
    void MyDialog::ExecuteCommand(const CString& command);

};
