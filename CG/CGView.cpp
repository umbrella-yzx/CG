
// CGView.cpp: CCGView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CG.h"
#endif

#include "CGDoc.h"
#include "CGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGView

IMPLEMENT_DYNCREATE(CCGView, CView)

BEGIN_MESSAGE_MAP(CCGView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCGView 构造/析构

CCGView::CCGView() noexcept
{
	// TODO: 在此处添加构造代码

}

CCGView::~CCGView()
{
}

BOOL CCGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCGView 绘图

void CCGView::OnDraw(CDC* /*pDC*/)
{
	CCGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CCGView 打印

BOOL CCGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CCGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CCGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CCGView 诊断

#ifdef _DEBUG
void CCGView::AssertValid() const
{
	CView::AssertValid();
}

void CCGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGDoc* CCGView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGDoc)));
	return (CCGDoc*)m_pDocument;
}
#endif //_DEBUG


// CCGView 消息处理程序
