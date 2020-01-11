
// Image_ProcessingView.cpp : CImage_ProcessingView ���ʵ��
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CImage_ProcessingView ����/����

CImage_ProcessingView::CImage_ProcessingView()
{
	// TODO: �ڴ˴���ӹ������

}

CImage_ProcessingView::~CImage_ProcessingView()
{
}

BOOL CImage_ProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CImage_ProcessingView ����

void CImage_ProcessingView::OnDraw(CDC* pDC)
{
	CImage_ProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImage_ProcessingView ��ӡ


void CImage_ProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImage_ProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImage_ProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImage_ProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CImage_ProcessingView ���

#ifdef _DEBUG
void CImage_ProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImage_ProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImage_ProcessingDoc)));
	return (CImage_ProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImage_ProcessingView ��Ϣ�������


void CImage_ProcessingView::OnFileOpen()
{
	// TODO: �ڴ���������������
	CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
	if(IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if(!m_Image.IsNull()) m_Image.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
		m_Image.Load(dlg.GetPathName());//���ͼƬ�ĵ�ַ�����Ҽ���ͼƬ

		//���ͼƬ�Ĵ�С���������С���ù������ĳ�ʼ���ڴ�С�Ȳ���
		CSize sizeTotal;
		int w=m_Image.GetWidth();
		int h=m_Image.GetHeight();
		sizeTotal.cx =w;
		sizeTotal.cy =h;
		SetScrollSizes(MM_TEXT, sizeTotal);

		//Window_Image_w=m_Image.GetWidth();//���ͼƬ�ĳ�ʼ��С��Ϊ�Ŵ���С������׼��
		//Window_Image_h=m_Image.GetHeight();//


		Invalidate(1); //ǿ�Ƶ���ONDRAW����
	}
}


void CImage_ProcessingView::OnDrawline()
{
	// TODO: �ڴ���������������
	if(m_Image.IsNull()) return;
	
	int w=m_Image.GetWidth();
	int h=m_Image.GetHeight();

	for (int k=0;k<w;k++)
	{
		m_Image.m_pBits[0][10][k]=0;//B
		m_Image.m_pBits[1][10][k]=0;//G
		m_Image.m_pBits[2][10][k]=0;//R


	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW����

}


void CImage_ProcessingView::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) {
		MessageBox(_T("�㻹û�д�һ��Ҫ�����ͼ���ļ���"));
		return;
	}
	CString strFilter;
	//strFilter ="λͼ�ļ�|*.bmp|JPEG ͼ���ļ�|*.jpg|GIF ͼ���ļ�|*.gif|PNG ͼ���ļ�|*.png||";   //
	strFilter ="�����ļ�|*.*||";   //

	CFileDialog dlg(FALSE,NULL,NULL,NULL,strFilter);
	//CFileDialog dlg(FALSE,NULL,NULL,NULL);

	if ( IDOK != dlg.DoModal()) 
		return;
	// ����û�û��ָ���ļ���չ������Ϊ�����һ��
	CString strFileName;
	//CString strExtension;
	strFileName = dlg.m_ofn.lpstrFile;   //  ����ļ���
	//if(dlg.m_ofn.nFileExtension == 0)     //����ļ���չ��
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
	// ͼ�񱣴�
	HRESULT hResult = m_Image.Save(strFileName);
	if (FAILED(hResult))
	{
		MessageBox(_T("����ͼ���ļ�ʧ�ܣ�"));
	}

}


void CImage_ProcessingView::OnShowred()
{
	// TODO: �ڴ���������������
	if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w=m_Image.GetWidth();//���ͼ��Ŀ��
	int h=m_Image.GetHeight();//���ͼ��ĸ߶�
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			m_Image.m_pBits[0][j][k]=0;//B   ��ѭ������ͼ�������ֵ����������ɫ��������ɫ������Ϊ0��ͼ���ֻʣ�º�ɫ������
			m_Image.m_pBits[1][j][k]=0;//G

		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}

/*void CImage_ProcessingView::OnReduceResolution()
{
	

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}*/

// --------------------------------------------------------------------------------------------------
//		������ͼ���ʣ�����ͼ��ֱ���
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnViewToolbar()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			m_Image.m_pBits[0][i / 2][j / 2] = m_Image.m_pBits[0][i][j];
			m_Image.m_pBits[1][i / 2][j / 2] = m_Image.m_pBits[1][i][j];
			m_Image.m_pBits[2][i / 2][j / 2] = m_Image.m_pBits[2][i][j];
			// --------------------------------------------------------------------------------------------------
			//		��������С��ͼƬ���пհ����
			//-------------------------------------------------------------------------------------------------
			if (i >= w / 2 || j >= h / 2){
				m_Image.m_pBits[0][i][j] = 255;
				m_Image.m_pBits[1][i][j] = 255;
				m_Image.m_pBits[2][i][j] = 255;
			}
		}
	}
	// --------------------------------------------------------------------------------------------------
	//		��������С��ͼƬ���пհ����
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
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}

void CImage_ProcessingView::OnImageClass()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j]/2)*2;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / 2) * 2;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / 2) * 2;
		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}
// --------------------------------------------------------------------------------------------------
//		��������̽�һ��256���ĻҶ�ͼ��ֽ�Ϊ168���Ҷȷֱ���
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnImageClass168()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		��������256��������������ֵӳ�䵽һ��
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / 2) * 2;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / 2) * 2;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / 2) * 2;
		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}
// --------------------------------------------------------------------------------------------------
//		��������̽�һ��256���ĻҶ�ͼ��ֽ�Ϊ64���Ҷȷֱ���
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnImageClass64()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		��������256������4������ֵӳ�䵽һ������0��1��2��3-->0��
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / 4) * 4;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / 4) * 4;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / 4) * 4;
		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}
void CImage_ProcessingView::OnImageClass32()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		��������256������8������ֵӳ�䵽һ������ֵ
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / 8) * 8;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] /8) * 8;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] /8) * 8;
		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}
void CImage_ProcessingView::OnImageClass16()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		��������256������16������ֵӳ�䵽һ��
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / 16) * 16;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / 16) * 16;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / 16) * 16;
		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}
void CImage_ProcessingView::OnImageClass8()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		��������256������32������ֵӳ�䵽һ��
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / 32) * 32;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / 32) * 32;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / 32) * 32;
		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}
void CImage_ProcessingView::OnImageClass4()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		��������256������64������ֵӳ�䵽һ��
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / 64) * 64;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / 64) * 64;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / 64) * 64;
		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}

void CImage_ProcessingView::OnImageClass2()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			// --------------------------------------------------------------------------------------------------
			//		��������256������128������ֵӳ�䵽һ��������ֵ������
			//-------------------------------------------------------------------------------------------------
			m_Image.m_pBits[0][i][j] = (int)(m_Image.m_pBits[0][i][j] / 128) >0 ? 255 : 0;
			m_Image.m_pBits[1][i][j] = (int)(m_Image.m_pBits[1][i][j] / 128) >0 ? 255 : 0;
			m_Image.m_pBits[2][i][j] = (int)(m_Image.m_pBits[2][i][j] / 128) >0 ? 255 : 0;
		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}
// --------------------------------------------------------------------------------------------------
//		������ʵ��ͼ����
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::ImageDifference()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	
	// --------------------------------------------------------------------------------------------------
	//		�������򿪵ڶ���ͼƬ���һ�������
	//-------------------------------------------------------------------------------------------------
	// TODO: �ڴ���������������
	CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
	if (IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		//if (!m_Image.IsNull()) m_Image.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
		mx_Image.Load(dlg.GetPathName());//���ͼƬ�ĵ�ַ�����Ҽ���ͼƬ

		//���ͼƬ�Ĵ�С���������С���ù������ĳ�ʼ���ڴ�С�Ȳ���
		CSize sizeTotal;
		int w = mx_Image.GetWidth();
		int h = mx_Image.GetHeight();
		sizeTotal.cx = w;
		sizeTotal.cy = h;
		SetScrollSizes(MM_TEXT, sizeTotal);
		Invalidate(1); //ǿ�Ƶ���ONDRAW����
	}
	if (mx_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
	Invalidate(1); //ǿ�Ƶ���ONDRAW����

}
// --------------------------------------------------------------------------------------------------
//		������6��ͼ�����ȥ��
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::ImageAdd()
{

	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int num = 1;
	while (num<6){
		
		CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
		if (IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
		{
			//if (!m_Image.IsNull()) m_Image.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
			x_Image[num].Load(dlg.GetPathName());//���ͼƬ�ĵ�ַ�����Ҽ���ͼƬ

			//���ͼƬ�Ĵ�С���������С���ù������ĳ�ʼ���ڴ�С�Ȳ���
			CSize sizeTotal;
			int w = x_Image[num].GetWidth();
			int h = x_Image[num].GetHeight();
			sizeTotal.cx = w;
			sizeTotal.cy = h;
			SetScrollSizes(MM_TEXT, sizeTotal);
			Invalidate(1); //ǿ�Ƶ���ONDRAW����
		}
		//if (mx_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
	//		������6��ͼ�����ȥ��
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
	
	Invalidate(1); //ǿ�Ƶ���ONDRAW����
}

// --------------------------------------------------------------------------------------------------
//		������ͳ������һ��ͼ���ֱ��ͼ����ʾ
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnHistogram()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();

	CImageZFTDlg dlg;
	
	//int ImagData[512];
	//memset(ImagData, 0, sizeof(ImagData));
	for (int j = 0; j<256; j++) { //�������鲢����
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
//		��������ɫͼ���һ��ͨ����ֱ��ͼ���⻯
//-------------------------------------------------------------------------------------------------

void CImage_ProcessingView::OnImageEqualization()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
	//		������ֻͳ��һ��ͨ���Ҷ�ֵ���Ҽ���Ҷ�ֵ����
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
	//		������ԭͼ���ֵ����⻯��ĻҶ�ֵӳ��
	//-------------------------------------------------------------------------------------------------
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++){
			int xx = m_Image.m_pBits[0][i][j];
			m_Image.m_pBits[0][i][j] = gray_equal[xx];
			m_Image.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
			m_Image.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
		}
	}
	Invalidate(1); //ǿ�Ƶ���ONDRAW����
}

// --------------------------------------------------------------------------------------------------
//		��������ɫͼ���һ��ͨ���ҶȵĹ涨��
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnImageNormalization()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();
	int h = m_Image.GetHeight();
	int gray[256] = { 0 };
	double gray_prob[256] = { 0 };
	double gray_distribution[256] = { 0 };
	int gray_equal[256] = { 0 };
	int gray_sum = w*h;
	// --------------------------------------------------------------------------------------------------
	//		���������һ��ͼ��ķֲ�����
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
	//		�������򿪵ڶ���ͼ�������ֲ����ʣ��Ե�һ��ͼ��涨��
	//-------------------------------------------------------------------------------------------------
	CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
	if (IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		//if (!m_Image.IsNull()) m_Image.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
		x_Image[0].Load(dlg.GetPathName());//���ͼƬ�ĵ�ַ�����Ҽ���ͼƬ

		//���ͼƬ�Ĵ�С���������С���ù������ĳ�ʼ���ڴ�С�Ȳ���
		CSize sizeTotal;
		int w = x_Image[0].GetWidth();
		int h = x_Image[0].GetHeight();
		sizeTotal.cx = w;
		sizeTotal.cy = h;
		SetScrollSizes(MM_TEXT, sizeTotal);
		Invalidate(1); //ǿ�Ƶ���ONDRAW����
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
	//		������������ͼ��ֲ�����������ֵ���ƥ��
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

	Invalidate(1); //ǿ�Ƶ���ONDRAW����
}

// --------------------------------------------------------------------------------------------------
//		����������������ͼ��������ֵ�˲������˲�����С3*3
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnImageMeanFiltering()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
	Invalidate(1); //ǿ�Ƶ���ONDRAW����
}

// --------------------------------------------------------------------------------------------------
//		����������������ͼ��������ֵ�˲������˲�����С3*3
//-------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnMedianFiltering()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
					//		������ͼ���Ե������Ϊ0����
					//-------------------------------------------------------------------------------------------------
					sx1[k] = 0;
					sx2[k] = 0;
					sx3[k] = 0;
				}
			}
			// --------------------------------------------------------------------------------------------------
			//		����������ͨ���ֱ����򣬵õ����м�ֵ
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

	Invalidate(1); //ǿ�Ƶ���ONDRAW����
}

// --------------------------------------------------------------------------------------------------
//		������FFT�任���Ƶ��ͼ��
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
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
	//		����������fft�õ���Ƶ��ͼ��û�������Ļ��������任���������Ƶ��ͼ���������
	//---------------------------------------------------------------------------------------------------
	Invalidate(1); //ǿ�Ƶ���ONDRAW����
}


// --------------------------------------------------------------------------------------------------
//		����������Ӧ��ֵ�˲�����ƣ����ֶ������ʼ�˲�ģ���С
//---------------------------------------------------------------------------------------------------

void CImage_ProcessingView::OnAotoFiltering()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull())
		return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	//CString str("��Сֵ�˲���");
	int k;
	EditDlg editdlg;
	// --------------------------------------------------------------------------------------------------
	//		�����������Ի��������ʼ�˲�ģ���С
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
					//����ģ���С
					currsize += 2;
					delete[] wind;
					wind = NULL;
				}
			}
		}
		//�Ա߽���д���
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
//		��������ɫͼ����ʾ��ɫ��������ɫ������ͨ��3
//---------------------------------------------------------------------------------------------------

void CImage_ProcessingView::OnShowRed()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
//		��������ɫͼ����ʾ��ɫ��������ɫ������ͨ��2
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnShowGreen()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
//		��������ɫͼ����ʾ��ɫ��������ɫ������ͨ��1
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnShowBlue()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
//		��������ɫͼ��RGB�ռ�ת����HSI�ռ�
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnShowHSI()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
			//	����S����
			S = 1 - static_cast<long double>(min(min(R_ch, G_ch), B_ch)) * 3 / (static_cast<int>(R_ch)+G_ch + B_ch);
			S_ch = 255 * S + 0.5;

			//	����I����
			I_ch = (static_cast<int>(R_ch)+G_ch + B_ch) / 3;
			m_Image.m_pBits[0][i][j] = H_ch;
			m_Image.m_pBits[1][i][j] = S_ch;
			m_Image.m_pBits[2][i][j] = I_ch;
		}
	}
	//Invalidate(1);
}
// --------------------------------------------------------------------------------------------------
//		��������ɫͼ��HSI�ռ䣬��I������ֱ��ͼ���⻯
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnHSIequalization()
{
	// TODO:  �ڴ���������������s
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
	Invalidate(1); //ǿ�Ƶ���ONDRAW����

}
// --------------------------------------------------------------------------------------------------
//		��������ɫͼ��RGB�ռ䣬����ͨ�������ֱ���ֱ��ͼ���⻯
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnRGBequalization()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
	Invalidate(1); //ǿ�Ƶ���ONDRAW����
}

// --------------------------------------------------------------------------------------------------
//		������RGB�ռ�ת����HSI�ռ䣬��ʾH�����Ҷ�ͼ��
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnShowH()
{
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
			//	����S����
			S = 1 - static_cast<long double>(min(min(R_ch, G_ch), B_ch)) * 3 / (static_cast<int>(R_ch)+G_ch + B_ch);
			S_ch = 255 * S + 0.5;

			//	����I����
			I_ch = (static_cast<int>(R_ch)+G_ch + B_ch) / 3;
			m_Image.m_pBits[0][i][j] = H_ch;
			m_Image.m_pBits[1][i][j] = H_ch;
			m_Image.m_pBits[2][i][j] = H_ch;
		}
	}
	Invalidate(1);
}
// --------------------------------------------------------------------------------------------------
//		������RGB�ռ�ת����HSI�ռ䣬��ʾS�����Ҷ�ͼ��
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnShowS()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
			//	����S����
			S = 1 - static_cast<long double>(min(min(R_ch, G_ch), B_ch)) * 3 / (static_cast<int>(R_ch)+G_ch + B_ch);
			S_ch = 255 * S + 0.5;

			//	����I����
			I_ch = (static_cast<int>(R_ch)+G_ch + B_ch) / 3;
			m_Image.m_pBits[0][i][j] = S_ch;
			m_Image.m_pBits[1][i][j] = S_ch;
			m_Image.m_pBits[2][i][j] = S_ch;
		}
	}
	Invalidate(1);
}

// --------------------------------------------------------------------------------------------------
//		������RGB�ռ�ת����HSI�ռ䣬��ʾI�����Ҷ�ͼ��
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnShowI()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
			//	����S����
			S = 1 - static_cast<long double>(min(min(R_ch, G_ch), B_ch)) * 3 / (static_cast<int>(R_ch)+G_ch + B_ch);
			S_ch = 255 * S + 0.5;

			//	����I����
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
//		������HOUGH�任�߶μ�⣬�������⣬δ���
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnHoughLines()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
//		����������ȫ����ֵ�㷨�ָ�ͼ��
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnThresholdSegment()
{
	// TODO:  �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
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
		//ƽ��ֵ
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
//		��������󷽲�ָ�ͼ�� 
//---------------------------------------------------------------------------------------------------
void CImage_ProcessingView::OnOtsuthreshold()
{
	// TODO:  �ڴ���������������
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
//		��������ɫͼ��ָ��Ӧ������ͼ������ɫͼ��ָ�֣���ͼ������ҶȾ�ֵ+-��ֵ�ָ����
//---------------------------------------------------------------------------------------------------

void CImage_ProcessingView::OnRGBDivision()
{
	// TODO:  �ڴ���������������
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
