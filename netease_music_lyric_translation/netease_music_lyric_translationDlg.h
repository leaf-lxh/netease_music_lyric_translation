
// netease_music_lyric_translationDlg.h: 头文件
//

#pragma once


// CneteasemusiclyrictranslationDlg 对话框
class CneteasemusiclyrictranslationDlg : public CDialogEx
{
// 构造
public:
	CneteasemusiclyrictranslationDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETEASE_MUSIC_LYRIC_TRANSLATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	
	CStatic label_message;
	CEdit edit_source;
	CEdit edit_translation;
	afx_msg void OnEnChangeEditSrc();
};
