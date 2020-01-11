
// Image_ProcessingView.cpp : CImage_ProcessingView 类的实现
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Image_Processing.h"
#endif

#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"
#include "ImageZFTDlg.h"
#include "EditDlg.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CImage_ProcessingView

IMPLEMENT_DYNCREATE(CImage_ProcessingView, CScrollView)

BEGIN_MESSAGE_MAP(CImage_ProcessingView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImage_ProcessingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_OPEN, &CImage_ProcessingView::OnFileOpen)
	ON_COMMAND(IDM_DRAWLINE, &CImage_ProcessingView::OnDrawline)
	ON_COMMAND(ID_FILE_SAVE_AS, &CImage_ProcessingView::OnFileSaveAs)
	ON_COMMAND(IDM_SHOWRED, &CImage_ProcessingView::OnShowred)
	//ON_COMMAND(IDM_SHOWRED, &CImage_ProcessingView::OnImageClass)
	ON_COMMAND(ID_32771, &CImage_ProcessingView::OnViewToolbar)
	ON_COMMAND(ID_32772, &CImage_ProcessingView::OnImageClass)
	ON_COMMAND(ID_32776, &CImage_ProcessingView::OnImageClass168)
	ON_COMMAND(ID_32777, &CImage_ProcessingView::OnImageClass64)
	ON_COMMAND(ID_32779, &CImage_ProcessingView::OnImageClass32)
	ON_COMMAND(ID_32780, &CImage_ProcessingView::OnImageClass16)
	ON_COMMAND(ID_32782, &CImage_ProcessingView::OnImageClass8)
	ON_COMMAND(ID_32783, &CImage_ProcessingView::OnImageClass4)
	ON_COMMAND(ID_32784, &CImage_ProcessingView::OnImageClass2)
	ON_COMMAND(ID_32785, &CImage_ProcessingView::ImageDifference)  
	ON_COMMAND(ID_32786, &CImage_ProcessingView::ImageAdd)
	ON_COMMAND(ID_ZFT_YT, &CImage_ProcessingView::OnHistogram)
	ON_COMMAND(ID_32789, &CImage_ProcessingView::OnImageEqualization)
	ON_COMMAND(ID_32790, &CImage_ProcessingView::OnImageNormalization)
	ON_COMMAND(ID_32791, &CImage_ProcessingView::OnImageMeanFiltering)
	ON_COMMAND(ID_32792, &CImage_ProcessingView::OnMedianFiltering)
	ON_COMMAND(ID_32793, &CImage_ProcessingView::OnImage_FFT)
	ON_COMMAND(ID_32794, &CImage_ProcessingView::OnAotoFiltering)
	ON_COMMAND(ID_32796, &CImage_ProcessingView::OnShowRed)
	ON_COMMAND(ID_32797, &CImage_ProcessingView::OnShowGreen)
	ON_COMMAND(ID_32798, &CImage_ProcessingView::OnShowBlue)
	ON_COMMAND(ID_RGB32800, &CImage_ProcessingView::OnShowH)
	ON_COMMAND(ID_RGB32801, &CImage_ProcessingView::OnShowS)
	ON_COMMAND(ID_RGB32802, &CImage_ProcessingView::OnShowI)
	ON_COMMAND(ID_32803, &CImage_ProcessingView::OnHoughLines)
	ON_COMMAND(ID_32804, &CImage_ProcessingView::OnThresholdSegment)
	ON_COMMAND(ID_32805, &CImage_ProcessingView::OnOtsuthreshold)
	ON_COMMAND(ID_32807, &CImage_ProcessingView::OnHSIequalization)
	ON_COMMAND(ID_32809, &CImage_ProcessingView::OnRGBequalization)
	ON_COMMAND(ID_32808, &CImage_ProcessingView::OnRGBDivision)
END_MESSAGE_MAP()

// CImage_ProcessingView 构造/析构

CImage_ProcessingView::CImage_ProcessingView()
{
	// TODO: 在此处添加构造代码

}

CImage_ProcessingView::~CImage_ProcessingView()
{
}

BOOL CImage_ProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CImage_ProcessingView 绘制

void CImage_ProcessingView::OnDraw(CDC* pDC)
{
	CImage_ProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (!m_Image.IsNull())
	{
		m_Image.Draw(pDC->m_hDC,0,0); 
	}
	return;
}

void CImage_ProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImage_ProcessingView 打印


void CImage_ProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImage_ProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImage_ProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImage_ProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CImage_ProcessingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImage_ProcessingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImage_ProcessingView 诊断

#ifdef _DEBUG
void CImage_ProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImage_ProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImage_ProcessingDoc)));
	return (CImage_ProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImage_ProcessingView 消息处理程序


void CImage_ProcessingView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(TRUE);    //为打开文件创建一个变量
	if(IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if(!m_Image.IsNull()) m_Image.Destroy();//判断是否已经有图片，有的话进行清除
		m_Image.Load(dlg.GetPathName());//获得图片的地址，并且加载图片

		//获得图片的大小，并按其大小设置滚动条的初始窗口大小等参数
		CSize sizeTotal;
		int w=m_Image.GetWidth();
		int h=m_Image.GetHeight();
		sizeTotal.cx =w;
		sizeTotal.cy =h;
		SetScrollSizes(MM_TEXT, sizeTotal);

		//Window_Image_w=m_Image.GetWidth();//获得图片的初始大小，为放大缩小功能做准备
		//Window_Image_h=m_Image.GetHeight();//


		Invalidate(1); //强制调用ONDRAW函数
	}
}


void CImage_ProcessingView::OnDrawline()
{
	// TODO: 在此添加命令处理程序代码
	if(m_Image.IsNull()) return;
	
	int w=m_Image.GetWidth();
	int h=m_Image.GetHeight();

	for (int k=0;k<w;k++)
	{
		m_Image.m_pBits[0][10][k]=0;//B
		m_Image.m_pBits[1][10][k]=0;//G
		m_Image.m_pBits[2][10][k]=0;//R


	}

	Invalidate(1); //强制调用ONDRAW函数

}


void CImage_ProcessingView::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) {
		MessageBox(_T("你还没有打开一个要保存的图像文件！"));
		return;
	}
	CString strFilter;
	//strFilter ="位图文件|*.bmp|JPEG 图像文件|*.jpg|GIF 图像文件|*.gif|PNG 图像文件|*.png||";   //
	strFilter ="所有文件|*.*||";   //

	CFileDialog dlg(FALSE,NULL,NULL,NULL,strFilter);
	//CFileDialog dlg(FALSE,NULL,NULL,NULL);

	if ( IDOK != dlg.DoModal()) 
		return;
	// 如果用户没有指定文件扩展名，则为其添加一个
	CString strFileName;
	//CString strExtension;
	strFileName = dlg.m_ofn.lpstrFile;   //  获得文件名
	//if(dlg.m_ofn.nFileExtension == 0)     //获得文件扩展名
	//{
	//	switch (dlg.m_ofn.nFilterIndex)
	//	{
	//	case 1:
	//		strExtension = "bmp"; break;
	//	case 2:
	//		strExtension = "jpg"; break;
	//	case 3:
	//		strExtension = "gif"; break;
	//	case 4:
	//		strExtension = "png"; break;
	//	default:
	//		break;
	//	}
	//	strFileName = strFileName + _T(".") + strExtension;
	//	//strFileName="C:\\Users\\Lenovo\\Desktop\\QSanguosha-Qingming\\abc.bmp";
	//}
	// 图像保存
	HRESULT hResult = m_Image.Save(strFileName);
	if (FAILED(hResult))
	{
		MessageBox(_T("保存图像文件失败！"));
	}

}


void CImage_ProcessingView::OnShowred()
{
	// TODO: 在此添加命令处理程序代码
	if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w=m_Image.GetWidth();//获得图像的宽度
	int h=m_Image.GetHeight();//获得图像的高度
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			m_Image.m_pBits[0][j][k]=0;//B   用循环访问图像的像素值，将它的绿色分量和蓝色分量置为0，图像就只剩下红色分量了
			m_Image.m_pBits[1][j][k]=0;//G

		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}

/*void CImage_ProcessingView::OnReduceResolution()
{
	

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}*/

// --------------------------------------------------------------------------------------------------
//		描述：图像将质，降低图像分辨率
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnViewToolbar()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			m_Image.m_pBits[0][i / 2][j / 2] = m_Image.m_pBits[0][i][j];
			m_Image.m_pBits[1][i / 2][j / 2] = m_Image.m_pBits[1][i][j];
			m_Image.m_pBits[2][i / 2][j / 2] = m_Image.m_pBits[2][i][j];
			// --------------------------------------------------------------------------------------------------
			//		描述：缩小后图片进行空白填充
			//-------------------------------------------------------------------------------------------------
			if (i >= w / 2 || j >= h / 2){
				m_Image.m_pBits[0][i][j] = 255;
				m_Image.m_pBits[1][i][j] = 255;
				m_Image.m_pBits[2][i][j] = 255;
			}
		}
	}
	// --------------------------------------------------------------------------------------------------
	//		描述：缩小后图片进行空白填充
	//-------------------------------------------------------------------------------------------------
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			if (i >= h / 2 || j >= w / 2){
				m_Image.m_pBits[0][i][j] = 255;
				m_Image.m_pBits[1][i][j] = 255;
				m_Image.m_pBits[2][i][j] = 255;
			}
		}
	}
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}

void CImage_ProcessingView::OnImageClass()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j]/2)*2;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / 2) * 2;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / 2) * 2;
		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}
// --------------------------------------------------------------------------------------------------
//		描述：编程将一幅256级的灰度图像分解为168级灰度分辨率
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnImageClass168()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		描述：将256级相邻两个像素值映射到一个
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / 2) * 2;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / 2) * 2;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / 2) * 2;
		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}
// --------------------------------------------------------------------------------------------------
//		描述：编程将一幅256级的灰度图像分解为64级灰度分辨率
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnImageClass64()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		描述：将256级相邻4个像素值映射到一个，（0，1，2，3-->0）
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / 4) * 4;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / 4) * 4;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / 4) * 4;
		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}
void CImage_ProcessingView::OnImageClass32()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		描述：将256级相邻8个像素值映射到一个像素值
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / 8) * 8;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] /8) * 8;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] /8) * 8;
		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}
void CImage_ProcessingView::OnImageClass16()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		描述：将256级相邻16个像素值映射到一个
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / 16) * 16;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / 16) * 16;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / 16) * 16;
		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}
void CImage_ProcessingView::OnImageClass8()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		描述：将256级相邻32个像素值映射到一个
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / 32) * 32;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / 32) * 32;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / 32) * 32;
		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}
void CImage_ProcessingView::OnImageClass4()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		描述：将256级相邻64个像素值映射到一个
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / 64) * 64;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / 64) * 64;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / 64) * 64;
		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}

void CImage_ProcessingView::OnImageClass2()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		描述：将256级相邻128个像素值映射到一个，做二值化处理
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (int)(m_Image.m_pBits[0][i][j] / 128) >0 ? 255 : 0;
			m_Image.m_pBits[1][i][j] = (int)(m_Image.m_pBits[1][i][j] / 128) >0 ? 255 : 0;
			m_Image.m_pBits[2][i][j] = (int)(m_Image.m_pBits[2][i][j] / 128) >0 ? 255 : 0;
		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}
// --------------------------------------------------------------------------------------------------
//		描述：实现图像差分
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::ImageDifference()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	
	// --------------------------------------------------------------------------------------------------
	//		描述：打开第二张图片与第一张做差分
	//-------------------------------------------------------------------------------------------------
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(TRUE);    //为打开文件创建一个变量
	if (IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		//if (!m_Image.IsNull()) m_Image.Destroy();//判断是否已经有图片，有的话进行清除
		mx_Image.Load(dlg.GetPathName());//获得图片的地址，并且加载图片

		//获得图片的大小，并按其大小设置滚动条的初始窗口大小等参数
		CSize sizeTotal;
		int w = mx_Image.GetWidth();
		int h = mx_Image.GetHeight();
		sizeTotal.cx = w;
		sizeTotal.cy = h;
		SetScrollSizes(MM_TEXT, sizeTotal);
		Invalidate(1); //强制调用ONDRAW函数
	}
	if (mx_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			m_Image.m_pBits[0][i][j] = abs(mx_Image.m_pBits[0][i][j] - m_Image.m_pBits[0][i][j]); 
			m_Image.m_pBits[1][i][j] = abs(mx_Image.m_pBits[1][i][j] - m_Image.m_pBits[1][i][j]);
			m_Image.m_pBits[2][i][j] = abs(mx_Image.m_pBits[2][i][j] - m_Image.m_pBits[2][i][j]);
		}
	}
	Invalidate(1); //强制调用ONDRAW函数

}
// --------------------------------------------------------------------------------------------------
//		描述：6幅图像相加去噪
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::ImageAdd()
{

	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int num = 1;
	while (num<6){
		
		CFileDialog dlg(TRUE);    //为打开文件创建一个变量
		if (IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
		{
			//if (!m_Image.IsNull()) m_Image.Destroy();//判断是否已经有图片，有的话进行清除
			x_Image[num].Load(dlg.GetPathName());//获得图片的地址，并且加载图片

			//获得图片的大小，并按其大小设置滚动条的初始窗口大小等参数
			CSize sizeTotal;
			int w = x_Image[num].GetWidth();
			int h = x_Image[num].GetHeight();
			sizeTotal.cx = w;
			sizeTotal.cy = h;
			SetScrollSizes(MM_TEXT, sizeTotal);
			Invalidate(1); //强制调用ONDRAW函数
		}
		//if (mx_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
		/*
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++){
				m_Image.m_pBits[0][i][j] = (x_Image[num].m_pBits[0][i][j] + m_Image.m_pBits[0][i][j])/2;
				m_Image.m_pBits[1][i][j] = (x_Image[num].m_pBits[1][i][j] + m_Image.m_pBits[1][i][j])/2;
				m_Image.m_pBits[2][i][j] = (x_Image[num].m_pBits[2][i][j] + m_Image.m_pBits[2][i][j])/2;
			}
		}
		*/
		num++;
	}
	// --------------------------------------------------------------------------------------------------
	//		描述：6幅图像相加去噪
	//-------------------------------------------------------------------------------------------------
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			int tmp1 = m_Image.m_pBits[0][i][j], tmp2 = m_Image.m_pBits[1][i][j], tmp3 = m_Image.m_pBits[2][i][j];
			for (int k = 1; k < 6; k++){
				m_Image.m_pBits[0][i][j] = (x_Image[k].m_pBits[0][i][j] + m_Image.m_pBits[0][i][j]);
				m_Image.m_pBits[1][i][j] = (x_Image[k].m_pBits[1][i][j] + m_Image.m_pBits[1][i][j]);
				m_Image.m_pBits[2][i][j] = (x_Image[k].m_pBits[2][i][j] + m_Image.m_pBits[2][i][j]);
		        
				tmp1 = (x_Image[k].m_pBits[0][i][j] + tmp1);
				tmp2 = (x_Image[k].m_pBits[1][i][j] + tmp2);
				tmp3 = (x_Image[k].m_pBits[2][i][j] + tmp3);
			}

			m_Image.m_pBits[0][i][j] = (int)(tmp1 / 6);
			m_Image.m_pBits[1][i][j] = (int)tmp2 / 6;
			m_Image.m_pBits[2][i][j] = (int)tmp3 / 6;
		}
	}
	
	Invalidate(1); //强制调用ONDRAW函数
}

// --------------------------------------------------------------------------------------------------
//		描述：统计任意一幅图像的直方图并显示
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnHistogram()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();

	CImageZFTDlg dlg;
	
	//int ImagData[512];
	//memset(ImagData, 0, sizeof(ImagData));
	for (int j = 0; j<256; j++) { //定义数组并清零
		Red[j] = 0;
		Green[j] = 0;
		Blue[j] = 0;
	}

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			int x= m_Image.m_pBits[0][i][j];
			Red[x]++;
			x = m_Image.m_pBits[1][i][j];
			Green[x]++;
			x = m_Image.m_pBits[2][i][j];
			Blue[x]++;
		}
	}
	
	dlg.Red = Red;
	dlg.Green = Green;
	dlg.Blue = Blue;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	
}
// --------------------------------------------------------------------------------------------------
//		描述：彩色图像第一个通道下直方图均衡化
//-------------------------------------------------------------------------------------------------

void CImage_ProcessingView::OnImageEqualization()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int gray[256] = { 0 };
	double gray_prob[256] = { 0 };
	double gray_distribution[256] = { 0 };
	int gray_equal[256] = { 0 };
	int gray_sum = w*h;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			m_Image.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
			m_Image.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
			int col = m_Image.m_pBits[0][i][j];
			gray[col]++;
		}
	}
	// --------------------------------------------------------------------------------------------------
	//		描述：只统计一个通道灰度值并且计算灰度值概率
	//-------------------------------------------------------------------------------------------------
	for (int i = 0; i < 256; i++){
		gray_prob[i] = gray[i]*1.0 / gray_sum*1.0;
	}
	gray_distribution[0] = gray_prob[0];
	for (int i = 1; i < 256; i++){
		gray_distribution[i] = gray_distribution[i - 1] + gray_prob[i];
	}
	for (int i = 0; i < 256; i++){
		gray_equal[i] = (int)(255 * gray_distribution[i] + 0.5);
	}
	// --------------------------------------------------------------------------------------------------
	//		描述：原图像的值与均衡化后的灰度值映射
	//-------------------------------------------------------------------------------------------------
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			int xx = m_Image.m_pBits[0][i][j];
			m_Image.m_pBits[0][i][j] = gray_equal[xx];
			m_Image.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
			m_Image.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
		}
	}
	Invalidate(1); //强制调用ONDRAW函数
}

// --------------------------------------------------------------------------------------------------
//		描述：彩色图像第一个通道灰度的规定化
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnImageNormalization()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int gray[256] = { 0 };
	double gray_prob[256] = { 0 };
	double gray_distribution[256] = { 0 };
	int gray_equal[256] = { 0 };
	int gray_sum = w*h;
	// --------------------------------------------------------------------------------------------------
	//		描述：求第一幅图像的分布概率
	//-------------------------------------------------------------------------------------------------
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			m_Image.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
			m_Image.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
			int col = m_Image.m_pBits[0][i][j];
			gray[col]++;
		}
	}
	for (int i = 0; i < 256; i++){
		gray_prob[i] = gray[i] * 1.0 / gray_sum*1.0;
	}
	gray_distribution[0] = gray_prob[0];
	for (int i = 1; i < 256; i++){
		gray_distribution[i] = gray_distribution[i - 1] + gray_prob[i];
	}

	// --------------------------------------------------------------------------------------------------
	//		描述：打开第二幅图像并求出其分布概率，对第一幅图像规定化
	//-------------------------------------------------------------------------------------------------
	CFileDialog dlg(TRUE);    //为打开文件创建一个变量
	if (IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		//if (!m_Image.IsNull()) m_Image.Destroy();//判断是否已经有图片，有的话进行清除
		x_Image[0].Load(dlg.GetPathName());//获得图片的地址，并且加载图片

		//获得图片的大小，并按其大小设置滚动条的初始窗口大小等参数
		CSize sizeTotal;
		int w = x_Image[0].GetWidth();
		int h = x_Image[0].GetHeight();
		sizeTotal.cx = w;
		sizeTotal.cy = h;
		SetScrollSizes(MM_TEXT, sizeTotal);
		Invalidate(1); //强制调用ONDRAW函数
	}
	int ww = x_Image[0].GetWidth();
	int hh = x_Image[0].GetHeight();
	int gray1[256] = { 0 };
	double gray_prob1[256] = { 0 };
	double gray_distribution1[256] = { 0 };
	int gray_equal1[256] = { 0 };
	int gray_sum1 = ww*hh;
	int HistMatch[256];
	for (int i = 0; i < hh; i++)
	{
		for (int j = 0; j < ww; j++){
			x_Image[0].m_pBits[1][i][j] = x_Image[0].m_pBits[0][i][j];
			x_Image[0].m_pBits[2][i][j] = x_Image[0].m_pBits[0][i][j];
			int col = x_Image[0].m_pBits[0][i][j];
			gray1[col]++;
		}
	}
	for (int i = 0; i < 256; i++){
		gray_prob1[i] = gray1[i] * 1.0 / gray_sum1*1.0;
	}
	gray_distribution1[0] = gray_prob1[0];
	for (int i = 1; i < 256; i++){
		gray_distribution1[i] = gray_distribution1[i - 1] + gray_prob1[i];
	}
	// --------------------------------------------------------------------------------------------------
	//		描述：由两幅图像分布概率做像素值间的匹配
	//-------------------------------------------------------------------------------------------------
	for (int i = 0; i < 256; i++){
		double mn = 1024;
		int f = 0;
		for (int j = 0; j < 256; j++){
			if (mn>abs(gray_distribution1[j] - gray_distribution[i])){
				mn = abs(gray_distribution1[j] - gray_distribution[i]);
				f = j;
			}
		}
		HistMatch[i] = f;
	}
	
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			int xx = m_Image.m_pBits[0][i][j];
			m_Image.m_pBits[0][i][j] = HistMatch[xx];
			m_Image.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
			m_Image.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
		}
	}

	Invalidate(1); //强制调用ONDRAW函数
}

// --------------------------------------------------------------------------------------------------
//		描述：在有噪声的图像上做均值滤波器，滤波器大小3*3
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnImageMeanFiltering()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int x, y, xx, yy;
	int sum1, sum2, sum3;
	int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
	int dy[] = { 0, 1, 0, -1, 1, -1, 1, -1};
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			sum1 = m_Image.m_pBits[0][i][j];
			sum2 = m_Image.m_pBits[1][i][j];
			sum3 = m_Image.m_pBits[2][i][j];
			for (int k = 0; k < 8; k++){
				xx =i+ dx[k];
				yy =j+ dy[k];
				if (xx >= 0 && xx < h&&yy >= 0 && yy < w){
					sum1 += m_Image.m_pBits[0][xx][yy];
					sum2 += m_Image.m_pBits[1][xx][yy];
					sum3 += m_Image.m_pBits[2][xx][yy];
				}
			}
			m_Image.m_pBits[0][i][j] = sum1 / 9;
			m_Image.m_pBits[1][i][j] = sum2 / 9;
			m_Image.m_pBits[2][i][j] = sum3 / 9;
		}
	}
	Invalidate(1); //强制调用ONDRAW函数
}

// --------------------------------------------------------------------------------------------------
//		描述：在有噪声的图像上做中值滤波器，滤波器大小3*3
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnMedianFiltering()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int x, y, xx, yy;
	int sum1, sum2, sum3;
	int dx[] = { 1, 0, -1, 0, 1, 1, -1, -1 };
	int dy[] = { 0, 1, 0, -1, 1, -1, 1, -1 };
    BYTE sx1[25], sx2[25], sx3[25];
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			sum1 = m_Image.m_pBits[0][i][j];
			sum2 = m_Image.m_pBits[1][i][j];
			sum3 = m_Image.m_pBits[2][i][j];
			for (int k = 0; k < 8; k++)
			{
				xx = i + dx[k];
				yy = j + dy[k];
				if (xx >= 0 && xx < h&&yy >= 0 && yy < w){
					sx1[k] = m_Image.m_pBits[0][xx][yy];
					sx2[k] = m_Image.m_pBits[1][xx][yy];
					sx3[k] = m_Image.m_pBits[2][xx][yy];
				}
				else{
					// --------------------------------------------------------------------------------------------------
					//		描述：图像边缘处补充为0处理
					//-------------------------------------------------------------------------------------------------
					sx1[k] = 0;
					sx2[k] = 0;
					sx3[k] = 0;
				}
			}
			// --------------------------------------------------------------------------------------------------
			//		描述：三个通道分别排序，得到其中间值
			//-------------------------------------------------------------------------------------------------
			sx1[8] = m_Image.m_pBits[0][i][j];
			sx2[8] = m_Image.m_pBits[1][i][j];
			sx3[8] = m_Image.m_pBits[2][i][j];
			sort(sx1, sx1 + 9);
			sort(sx2, sx2 + 9);
			sort(sx3, sx3 + 9);
			m_Image.m_pBits[0][i][j] = sx1[4];
			m_Image.m_pBits[1][i][j] = sx2[4];
			m_Image.m_pBits[2][i][j] = sx3[4];
		}
	}

	Invalidate(1); //强制调用ONDRAW函数
}

// --------------------------------------------------------------------------------------------------
//		描述：FFT变换获得频谱图像
//-------------------------------------------------------------------------------------------------

//#define _CRT_SECURE_NO_WARNINGS
#define intsize sizeof(int)
#define complexsize sizeof(complex)
#define PI 3.1415926


int *a, *b;
int nLen, init_nLen, mLen, init_mLen, N, M;
FILE *dataFile;


typedef struct {
	float real;
	float image;
}complex;


complex *A, *A_In, *W;

complex Add(complex, complex);
complex Sub(complex, complex);
complex Mul(complex, complex);
int calculate_M(int);
void reverse(int, int);
void readData();
void fft(int, int);


void fft(int fft_nLen, int fft_M)
{
	int i;
	int lev, dist, p, t;
	complex B;


	W = (complex *)malloc(complexsize*fft_nLen / 2);


	for (lev = 1; lev <= fft_M; lev++)
	{
		dist = (int)pow(2, lev - 1);
		for (t = 0; t<dist; t++)
		{
			p = t*(int)pow(2, fft_M - lev);
			W[p].real = (float)cos(2 * PI*p / fft_nLen);
			W[p].image = (float)(-1 * sin(2 * PI*p / fft_nLen));
			for (i = t; i<fft_nLen; i = i + (int)pow(2, lev))
			{
				B = Add(A[i], Mul(A[i + dist], W[p]));
				A[i + dist] = Sub(A[i], Mul(A[i + dist], W[p]));
				A[i].real = B.real;
				A[i].image = B.image;
			}
		}
	}


	free(W);
}


int calculate_M(int len)
{
	int i;
	int k;

	i = 0;
	k = 1;
	while (k < len)
	{
		k = k * 2;
		i++;
	}

	return i;
}


void reverse(int len, int M)
{
	int i, j;

	a = (int *)malloc(intsize*M);
	b = (int *)malloc(intsize*len);

	for (i = 0; i<M; i++)
	{
		a[i] = 0;
	}

	b[0] = 0;
	for (i = 1; i<len; i++)
	{
		j = 0;
		while (a[j] != 0)
		{
			a[j] = 0;
			j++;
		}

		a[j] = 1;
		b[i] = 0;
		for (j = 0; j<M; j++)
		{
			b[i] = b[i] + a[j] * (int)pow(2, M - 1 - j);
		}
	}
}


complex Add(complex c1, complex c2)
{
	complex c;
	c.real = c1.real + c2.real;
	c.image = c1.image + c2.image;
	return c;
}


complex Sub(complex c1, complex c2)
{
	complex c;
	c.real = c1.real - c2.real;
	c.image = c1.image - c2.image;
	return c;
}


complex Mul(complex c1, complex c2)
{
	complex c;
	c.real = c1.real*c2.real - c1.image*c2.image;
	c.image = c1.real*c2.image + c2.real*c1.image;
	return c;
}

void CImage_ProcessingView::OnImage_FFT()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int i, j;
	
	M = calculate_M(h);
	N = calculate_M(w);
	nLen = (int)pow(2, N);
	mLen = (int)pow(2, M);

	A_In = (complex *)malloc(complexsize*nLen*mLen);
	for (i = 0; i<h; i++)
	{
		for (j = 0; j<w; j++)
		{
			A_In[i*nLen + j].real = m_Image.m_pBits[0][i][j]*pow(-1,i+j)*1.0;
			A_In[i*nLen + j].image = 0.0;
		}
	}
	for (i = 0; i<mLen; i++)
	{
		for (j = h; j<nLen; j++)
		{
			A_In[i*nLen + j].real = 0.0;
			A_In[i*nLen + j].image = 0.0;
		}
	}


	for (i = w; i<mLen; i++)
	{
		for (j = 0; j<h; j++)
		{
			A_In[i*nLen + j].real = 0.0;
			A_In[i*nLen + j].image = 0.0;
		}
	}




	A = (complex *)malloc(complexsize*nLen);
	reverse(nLen, N);
	for (i = 0; i<mLen; i++)
	{
		for (j = 0; j<nLen; j++)
		{
			A[j].real = A_In[i*nLen + b[j]].real;
			A[j].image = A_In[i*nLen + b[j]].image;
		}

		fft(nLen, N);
		for (j = 0; j<nLen; j++)
		{
			A_In[i*nLen + j].real = A[j].real;
			A_In[i*nLen + j].image = A[j].image;
		}
	}
	free(A);

	A = (complex *)malloc(complexsize*mLen);
	reverse(mLen, M);
	for (i = 0; i<nLen; i++)
	{
		for (j = 0; j<mLen; j++)
		{
			A[j].real = A_In[b[j] * nLen + i].real;
			A[j].image = A_In[b[j] * nLen + i].image;
		}

		fft(mLen, M);
		for (j = 0; j<mLen; j++)
		{
			A_In[j*nLen + i].real = A[j].real;
			A_In[j*nLen + i].image = A[j].image;
		}
	}
	free(A);
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++){
			m_Image.m_pBits[0][i][j] = (int)sqrt(A_In[i*nLen + j].real*A_In[i*nLen + j].real + A_In[i*nLen + j].image*A_In[i*nLen + j].image);
			m_Image.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
			m_Image.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
		}
	}
	// --------------------------------------------------------------------------------------------------
	//		描述：其中fft得到的频谱图像没有做中心化，对数变换操作，因此频谱图像存在问题
	//---------------------------------------------------------------------------------------------------
	Invalidate(1); //强制调用ONDRAW函数
}


// --------------------------------------------------------------------------------------------------
//		描述：自适应中值滤波器设计，可手动输入初始滤波模板大小
//---------------------------------------------------------------------------------------------------

void CImage_ProcessingView::OnAotoFiltering()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull())
		return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	//CString str("最小值滤波核");
	int k;
	EditDlg editdlg;
	// --------------------------------------------------------------------------------------------------
	//		描述：弹出对话框，输入初始滤波模板大小
	//---------------------------------------------------------------------------------------------------	
	if (editdlg.DoModal() == IDOK)
	{
		k = editdlg.m_Edit3;
		AotoFiltering(k);
	}
	Invalidate(TRUE);
}

void CImage_ProcessingView::AotoFiltering(int ksize)
{
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int pos = (ksize - 1) / 2;
	int i, j;
	for (int ch = 0; ch < 3; ch++){

		for (int m = pos; m < h - pos; m++)
		{
			for (int n = pos; n < w - pos; n++){
				int currsize = 3;
				while (currsize <= ksize)
				{
					int curpos = (currsize - 1) / 2;
					int winpos = 0;
					int lens = currsize*currsize;
					int* wind = new int[lens];
					//int wind[10024];
					for (i = -curpos; i <= curpos; i++){
						for (int j = -curpos; j <= curpos; j++)
							wind[winpos++] = m_Image.m_pBits[ch][m + i][n + j];
					}
					sort(wind, wind+lens);
					int fmin = wind[0];
					int fmax = wind[lens - 1];
					int fmed = wind[(lens - 1) / 2];
					int a1 = fmed - fmin;
					int a2 = fmed - fmax;
					if (a1 > 0 && a2 < 0)
					{
						int b1 = m_Image.m_pBits[ch][m][n]-fmin;
						int b2 = m_Image.m_pBits[ch][m][n] - fmax;
						if (b1>0 && b2 < 0)
							m_Image.m_pBits[ch][m][n] = m_Image.m_pBits[ch][m][n];
						else
							m_Image.m_pBits[ch][m][n] = fmed;

						delete[] wind;
						wind = NULL;
						break;
					}
					//增加模板大小
					currsize += 2;
					delete[] wind;
					wind = NULL;
				}
			}
		}
		//对边界进行处理
		for (int k = 0; k < pos; k++)
		for (int l = pos; l < w - pos; l++)
			m_Image.m_pBits[ch][k][l] = m_Image.m_pBits[ch][pos][l];
		for (int a = h - pos; a < h; a++)
		for (int b = pos; b < w - pos; b++)
			m_Image.m_pBits[ch][a][b] = m_Image.m_pBits[ch][h-pos-1][b];
		for (int c = 0; c < pos; c++)
		for (int d = 0; d < h; d++)
			m_Image.m_pBits[ch][d][c] = m_Image.m_pBits[ch][d][pos];
		for (int e = w - pos; e < w; e++)
		for (int f = 0; f < h; f++)
			m_Image.m_pBits[ch][f][e] = m_Image.m_pBits[ch][f][w-pos-1];
	}
	Invalidate(1);
}

// --------------------------------------------------------------------------------------------------
//		描述：彩色图像显示红色分量，红色分量是通道3
//---------------------------------------------------------------------------------------------------

void CImage_ProcessingView::OnShowRed()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			m_Image.m_pBits[0][i][j] = 0;
			m_Image.m_pBits[1][i][j] = 0;
		}
	}
	Invalidate(1);
}

// --------------------------------------------------------------------------------------------------
//		描述：彩色图像显示绿色分量，绿色分量是通道2
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnShowGreen()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			m_Image.m_pBits[0][i][j] = 0;
			m_Image.m_pBits[2][i][j] = 0;
		}
	}
	Invalidate(1);
}

// --------------------------------------------------------------------------------------------------
//		描述：彩色图像显示蓝色分量，蓝色分量是通道1
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnShowBlue()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			m_Image.m_pBits[1][i][j] = 0;
			m_Image.m_pBits[2][i][j] = 0;
		}
	}
	Invalidate(1);
}

// --------------------------------------------------------------------------------------------------
//		描述：彩色图像RGB空间转换到HSI空间
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnShowHSI()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int B_ch, G_ch, R_ch;
	double RG, RB, GB,thea;
	double H, S;
	unsigned char H_ch, S_ch, I_ch;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			B_ch = m_Image.m_pBits[0][i][j];
			G_ch = m_Image.m_pBits[1][i][j];
			R_ch = m_Image.m_pBits[2][i][j];
			RG = R_ch - G_ch;
			RB = R_ch - B_ch;
			GB = G_ch - B_ch;
			thea = acosl(0.5*(RG + RB) / sqrt(RG *RG + RB*GB));
			if (B_ch>G_ch)  H = 2 * 3.1415926 - thea;
			else
			{
				H = thea;
			}
			H_ch = (unsigned char)(255 * H / 3.1415926 + 0.5);
			//	计算S分量
			S = 1 - static_cast<long double>(min(min(R_ch, G_ch), B_ch)) * 3 / (static_cast<int>(R_ch)+G_ch + B_ch);
			S_ch = 255 * S + 0.5;

			//	计算I分量
			I_ch = (static_cast<int>(R_ch)+G_ch + B_ch) / 3;
			m_Image.m_pBits[0][i][j] = H_ch;
			m_Image.m_pBits[1][i][j] = S_ch;
			m_Image.m_pBits[2][i][j] = I_ch;
		}
	}
	//Invalidate(1);
}
// --------------------------------------------------------------------------------------------------
//		描述：彩色图像HSI空间，对I分量做直方图均衡化
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnHSIequalization()
{
	// TODO:  在此添加命令处理程序代码s
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	OnShowHSI();
	int gray[256] = { 0 };
	double gray_prob[256] = { 0 };
	double gray_distribution[256] = { 0 };
	int gray_equal[256] = { 0 };
	int gray_sum = w*h;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			//m_Image.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
			//m_Image.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
			int col = m_Image.m_pBits[2][i][j];
			gray[col]++;
		}
	}
	for (int i = 0; i < 256; i++){
		gray_prob[i] = gray[i] * 1.0 / gray_sum*1.0;
	}
	gray_distribution[0] = gray_prob[0];
	for (int i = 1; i < 256; i++){
		gray_distribution[i] = gray_distribution[i - 1] + gray_prob[i];
	}
	for (int i = 0; i < 256; i++){
		gray_equal[i] = (int)(255 * gray_distribution[i] + 0.5);
	}

	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			int xx = m_Image.m_pBits[2][i][j];
			m_Image.m_pBits[2][i][j] = gray_equal[xx];
			//m_Image.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
			//m_Image.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
		}
	}
	Invalidate(1); //强制调用ONDRAW函数

}
// --------------------------------------------------------------------------------------------------
//		描述：彩色图像RGB空间，对三通道分量分别做直方图均衡化
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnRGBequalization()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int ch = 0; ch < 3; ch++)
	{
		int gray[256] = { 0 };
		double gray_prob[256] = { 0 };
		double gray_distribution[256] = { 0 };
		int gray_equal[256] = { 0 };
		int gray_sum = w*h;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++){
				//m_Image.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
				//m_Image.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
				int col = m_Image.m_pBits[ch][i][j];
				gray[col]++;
			}
		}
		for (int i = 0; i < 256; i++){
			gray_prob[i] = gray[i] * 1.0 / gray_sum*1.0;
		}
		gray_distribution[0] = gray_prob[0];
		for (int i = 1; i < 256; i++){
			gray_distribution[i] = gray_distribution[i - 1] + gray_prob[i];
		}
		for (int i = 0; i < 256; i++){
			gray_equal[i] = (int)(255 * gray_distribution[i] + 0.5);
		}

		for (int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				int xx = m_Image.m_pBits[ch][i][j];
				m_Image.m_pBits[ch][i][j] = gray_equal[xx];
				//m_Image.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
				//m_Image.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
			}
		}
	}
	Invalidate(1); //强制调用ONDRAW函数
}

// --------------------------------------------------------------------------------------------------
//		描述：RGB空间转化到HSI空间，显示H分量灰度图像
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnShowH()
{
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	//OnShowHSI();
	int B_ch, G_ch, R_ch;
	double RG, RB, GB, thea;
	double H, S;
	unsigned char H_ch, S_ch, I_ch;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			B_ch = m_Image.m_pBits[0][i][j];
			G_ch = m_Image.m_pBits[1][i][j];
			R_ch = m_Image.m_pBits[2][i][j];
			RG = R_ch - G_ch;
			RB = R_ch - B_ch;
			GB = G_ch - B_ch;
			thea = acosl(0.5*(RG + RB) / sqrt(RG *RG + RB*GB));
			if (B_ch>G_ch)  H = 2 * 3.1415926 - thea;
			else
			{
				H = thea;
			}
			H_ch = (unsigned char)(255 * H / 3.1415926 + 0.5);
			//	计算S分量
			S = 1 - static_cast<long double>(min(min(R_ch, G_ch), B_ch)) * 3 / (static_cast<int>(R_ch)+G_ch + B_ch);
			S_ch = 255 * S + 0.5;

			//	计算I分量
			I_ch = (static_cast<int>(R_ch)+G_ch + B_ch) / 3;
			m_Image.m_pBits[0][i][j] = H_ch;
			m_Image.m_pBits[1][i][j] = H_ch;
			m_Image.m_pBits[2][i][j] = H_ch;
		}
	}
	Invalidate(1);
}
// --------------------------------------------------------------------------------------------------
//		描述：RGB空间转化到HSI空间，显示S分量灰度图像
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnShowS()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int B_ch, G_ch, R_ch;
	double RG, RB, GB, thea;
	double H, S;
	unsigned char H_ch, S_ch, I_ch;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			B_ch = m_Image.m_pBits[0][i][j];
			G_ch = m_Image.m_pBits[1][i][j];
			R_ch = m_Image.m_pBits[2][i][j];
			RG = R_ch - G_ch;
			RB = R_ch - B_ch;
			GB = G_ch - B_ch;
			thea = acosl(0.5*(RG + RB) / sqrt(RG *RG + RB*GB));
			if (B_ch>G_ch)  H = 2 * 3.1415926 - thea;
			else
			{
				H = thea;
			}
			H_ch = (unsigned char)(255 * H / 3.1415926 + 0.5);
			//	计算S分量
			S = 1 - static_cast<long double>(min(min(R_ch, G_ch), B_ch)) * 3 / (static_cast<int>(R_ch)+G_ch + B_ch);
			S_ch = 255 * S + 0.5;

			//	计算I分量
			I_ch = (static_cast<int>(R_ch)+G_ch + B_ch) / 3;
			m_Image.m_pBits[0][i][j] = S_ch;
			m_Image.m_pBits[1][i][j] = S_ch;
			m_Image.m_pBits[2][i][j] = S_ch;
		}
	}
	Invalidate(1);
}

// --------------------------------------------------------------------------------------------------
//		描述：RGB空间转化到HSI空间，显示I分量灰度图像
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnShowI()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int B_ch, G_ch, R_ch;
	double RG, RB, GB, thea;
	double H, S;
	unsigned char H_ch, S_ch, I_ch;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			B_ch = m_Image.m_pBits[0][i][j];
			G_ch = m_Image.m_pBits[1][i][j];
			R_ch = m_Image.m_pBits[2][i][j];
			RG = R_ch - G_ch;
			RB = R_ch - B_ch;
			GB = G_ch - B_ch;
			thea = acosl(0.5*(RG + RB) / sqrt(RG *RG + RB*GB));
			if (B_ch>G_ch)  H = 2 * 3.1415926 - thea;
			else
			{
				H = thea;
			}
			H_ch = (unsigned char)(255 * H / 3.1415926 + 0.5);
			//	计算S分量
			S = 1 - static_cast<long double>(min(min(R_ch, G_ch), B_ch)) * 3 / (static_cast<int>(R_ch)+G_ch + B_ch);
			S_ch = 255 * S + 0.5;

			//	计算I分量
			I_ch = (static_cast<int>(R_ch)+G_ch + B_ch) / 3;
			m_Image.m_pBits[0][i][j] = I_ch;
			m_Image.m_pBits[1][i][j] = I_ch;
			m_Image.m_pBits[2][i][j] = I_ch;
		}
	}
	Invalidate(1);
}

bool cmp(int x, int y)
{
	return x > y;
}
// --------------------------------------------------------------------------------------------------
//		描述：HOUGH变换线段检测，存在问题，未完成
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnHoughLines()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++){
			
			if (m_Image.m_pBits[0][i][j] >= 128)
				m_Image.m_pBits[0][i][j] = 255;
			else
				m_Image.m_pBits[0][i][j] = 0;
			m_Image.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
			m_Image.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
		}
	}
	

	double sin_value[200];
	double cos_value[200];
	int mx = (int)(max(w, h)*sqrtl(2))+1;
	int hough_acc[1000][200];
	for (int i = -90; i < 90; i++)
	{
		sin_value[i + 90] = sin(i*3.1415926 / 180);
		cos_value[i + 90] = cos(i*3.1415926 / 180);
	}
	int tp;
	int* hough_num;
	hough_num = (int*)malloc(181 * 1000 * sizeof(int));
	memset(hough_acc, 0, sizeof(hough_acc));
	memset(hough_num, 0, 181 * 1000 * sizeof(int));
	int tpp=0;
	for (int y = 0; y < h; y++)
	{
		for (int x = 0; x < w; x++)
		{
			if (m_Image.m_pBits[0][y][x]==0)  continue;
			for (int i = 0; i < 180; i++)
			{
				tp = (int)(x*sin_value[i] + y*cos_value[i]);
				hough_acc[tp][i] += 1;
				hough_num[tp * 181 + i] += 1;
				tpp = max(tpp, tp * 181 + i);
			}
		}
	}
	sort(hough_num, hough_num + tpp,cmp);
	
	Invalidate(1);
}

// --------------------------------------------------------------------------------------------------
//		描述：基本全局阈值算法分割图像
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnThresholdSegment()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	double im_sum = 0, im_ave = 0, im_ave1 = 0;
	int index = 0;
	double m1_sum = 0, m2_sum = 0;
	int m1_num = 0, m2_num = 0;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			im_sum += m_Image.m_pBits[0][i][j];
		}
	}
	im_ave = im_sum / (h*w);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (m_Image.m_pBits[0][i][j] <= im_ave){
				m1_sum += m_Image.m_pBits[0][i][j];
				m1_num++;
			}
			else{
				m2_sum += m_Image.m_pBits[0][i][j];
				m2_num++;
			}
		}
	}
	double m1 = 0, m2 = 0;
	if (m1_num != 0) m1 = m1_sum / m1_num;
	if (m2_num != 0) m2 = m2_sum / m2_num;
	double delt = 0.5;
	while (fabs(im_ave - (0.5*(m1 + m2))) > delt)
	{
		im_ave = 0.5*(m1 + m2);
		m1_sum = 0.0;
		m2_sum = 0.0;
		m1_num = 0;
		m2_num = 0;
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				//index = i * width + j;
				if (m_Image.m_pBits[0][i][j] <= im_ave)
				{
					m1_sum += m_Image.m_pBits[0][i][j];
					m1_num++;
				}
				else
				{
					m2_sum += m_Image.m_pBits[0][i][j];
					m2_num++;
				}
			}
		}
		//平均值
		if (m1_num != 0)
			m1 = m1_sum / m1_num;

		if (m2_num != 0)
			m2 = m2_sum / m2_num;
	}
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			//index = i * width + j;
			if (m_Image.m_pBits[0][i][j] <= im_ave)
			{
				m_Image.m_pBits[0][i][j] = 0;
				m_Image.m_pBits[1][i][j] = 0;
				m_Image.m_pBits[2][i][j] = 0;
			}
			else
			{
				m_Image.m_pBits[0][i][j] = 255;
				m_Image.m_pBits[1][i][j] = 255;
				m_Image.m_pBits[2][i][j] = 255;
			}
		}
	}
	Invalidate(1);
}

	
// --------------------------------------------------------------------------------------------------
//		描述：最大方差法分割图像 
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnOtsuthreshold()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	
	m_Image.m_OBits = (BYTE***)new BYTE**[3];  	
	for (int i = 0; i<3; i++)
	{
		m_Image.m_OBits[i] = (BYTE**)new BYTE*[h];
	}
	for (int i = 0; i<3; i++)
	{
		for (int j = 0; j<h; j++)
		{
			m_Image.m_OBits[i][j] = new BYTE[w];
		}
	}

	int count[256];
	memset(count, 0, sizeof(int)* 256);
	for (int j = 0; j<h; j++)
	{
		for (int k = 0; k<w; k++)
		{
			(count[m_Image.m_pBits[0][j][k]])++;
		}
	}

	double P1, Mk;
	double Mg = 0;
	int kk, Bestk;
	double fVaria, fMaxVaria = 0;
	for (int i = 0; i<256; i++)
	{
		Mg += i*count[i] / (w*h);
	}
	for (kk = 0; kk<256; kk++)
	{
		P1 = 0;
		Mk = 0;
		for (int i = 0; i <= kk; i++)
		{
			P1 += count[i] / (w*h);
			Mk += i*count[i] / (w*h);
		}
		fVaria = pow((Mg*P1 - Mk), 2) / (P1*(1 - P1));
		if (fVaria>fMaxVaria)
		{
			fMaxVaria = fVaria;
			Bestk = kk;
		}
	}
	for (int j = 0; j<h; j++)
	{
		for (int k = 0; k<w; k++)
		{
			if (m_Image.m_pBits[0][j][k]>Bestk)
			{
				m_Image.m_OBits[0][j][k] = 255;
			}
			else
			{
				m_Image.m_OBits[0][j][k] = 0;
			}
		}
	}
	for (int j = 0; j<h; j++)
	{
		for (int k = 0; k<w; k++)
		{
			m_Image.m_pBits[0][j][k] = m_Image.m_OBits[0][j][k];
			m_Image.m_pBits[1][j][k] = m_Image.m_OBits[0][j][k];
			m_Image.m_pBits[2][j][k] = m_Image.m_OBits[0][j][k];
		}
	}
	Invalidate(1);
	delete[]m_Image.m_OBits;
}


// --------------------------------------------------------------------------------------------------
//		描述：彩色图像分割，对应《数字图像处理》彩色图像分割部分，将图像整体灰度均值+-阈值分割出来
//---------------------------------------------------------------------------------------------------

void CImage_ProcessingView::OnRGBDivision()
{
	// TODO:  在此添加命令处理程序代码
	if (m_Image.IsNull()) return;
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int m1=0, m2=0, m3=0;
	int deta=6;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			m1 += m_Image.m_pBits[0][i][j];
			m2 += m_Image.m_pBits[1][i][j];
			m3 += m_Image.m_pBits[2][i][j];
		}
	}
	m1 /= (h*w);
	m2 /= (h*w);
	m3 /= (h*w);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (m_Image.m_pBits[0][i][j] >= m1 - deta&&m_Image.m_pBits[0][i][j] <= m1 + deta){
				m_Image.m_pBits[0][i][j] = 255;
			}else
				m_Image.m_pBits[0][i][j] = 0;
			if (m_Image.m_pBits[1][i][j] >= m2 - deta&&m_Image.m_pBits[1][i][j] <= m2 + deta){
				m_Image.m_pBits[1][i][j] = 255;
			}
			else
				m_Image.m_pBits[1][i][j] = 0;
			if (m_Image.m_pBits[2][i][j] >= m3 - deta&&m_Image.m_pBits[2][i][j] <= m3 + deta){
				m_Image.m_pBits[2][i][j] = 255;
			}
			else
				m_Image.m_pBits[2][i][j] = 0;
		}
	}
	Invalidate(1);
}
