#include "pch.h"
#include "MFC_CaphyonApp.h"
#include "MyDialog.h"
#include <string>

IMPLEMENT_DYNAMIC(MyDialog, CDialogEx)

MyDialog::MyDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG1, pParent)
{
}

MyDialog::~MyDialog()
{
}

void MyDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDCANCEL, Cancel);
    DDX_Control(pDX, IDOK, OK);
    DDX_Control(pDX, IDC_EDIT1, Edit);
    DDX_Control(pDX, IDC_EDIT2, OutputEdit);
    DDX_Control(pDX, IDC_BUTTON1, Browse);
    DDX_Control(pDX, IDC_LOGO, Logo);
}

BEGIN_MESSAGE_MAP(MyDialog, CDialogEx)
    ON_BN_CLICKED(IDCANCEL, &MyDialog::OnBnClickedCancel)
    ON_BN_CLICKED(IDOK, &MyDialog::OnBnClickedOk)
    ON_EN_CHANGE(IDC_EDIT2, &MyDialog::OnEnChangeEdit2)
    ON_BN_CLICKED(IDC_BUTTON1, &MyDialog::OnBnClickedBrowse)
    ON_STN_CLICKED(IDC_LOGO, &MyDialog::OnStnClickedLogo)
END_MESSAGE_MAP()

void MyDialog::OnBnClickedCancel()
{
    CDialogEx::OnCancel();
}

void MyDialog::OnBnClickedOk()
{
    CString strExeName;
    Edit.GetWindowText(strExeName);

    if (strExeName.IsEmpty())
    {
        AfxMessageBox(_T("Please select an executable file."));
        return;
    }

    SECURITY_ATTRIBUTES saAttr;
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0))
    {
        AfxMessageBox(_T("Error creating pipe."));
        return;
    }

    if (!SetHandleInformation(hChildStdoutRd, HANDLE_FLAG_INHERIT, 0))
    {
        AfxMessageBox(_T("Error setting handle information."));
        return;
    }

    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdOutput = hChildStdoutWr;
    si.hStdError = hChildStdoutWr;

    if (!CreateProcess(NULL, strExeName.GetBuffer(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        AfxMessageBox(_T("Error creating process."));
        return;
    }

    CloseHandle(hChildStdoutWr);

    DWORD dwRead;
    CHAR chBuf[4096];
    std::string strOutput;
    BOOL bSuccess = FALSE;
    while (ReadFile(hChildStdoutRd, chBuf, 4096, &dwRead, NULL) != FALSE && dwRead != 0)
    {
        bSuccess = TRUE;
        strOutput.append(chBuf, dwRead);
    }

    CloseHandle(hChildStdoutRd);

    if (bSuccess)
    {
        OutputEdit.SetWindowText(CString(strOutput.c_str()));
    }
    else
    {
        OutputEdit.SetWindowText(_T("Error reading output"));
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    Cancel.SetWindowText(_T("Close"));
}

void MyDialog::OnEnChangeEdit2()
{
}

void MyDialog::OnBnClickedBrowse()
{
    CString strFilter = _T("Executable Files (*.exe)|*.exe|All Files (*.*)|*.*||");
    CFileDialog dlg(TRUE, _T("exe"), NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, strFilter, this);

    if (dlg.DoModal() == IDOK)
    {
        CString strFilePath = dlg.GetPathName();
        Edit.SetWindowText(strFilePath);
    }
}
void MyDialog::OnStnClickedLogo()
{
}

BOOL MyDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    HENHMETAFILE hMetafile = GetEnhMetaFile(_T("logo.emf"));
    if (hMetafile != NULL)
    {
    
        Logo.SetEnhMetaFile(hMetafile);
    }

    return TRUE;
}


