/**************************************************************************************
 * File name: GlobalSettings.cpp
 *
 * Project: MapWindow Open Source (MapWinGis ActiveX control) 
 * Description: Implementation of CGlobalSettings
 *
 **************************************************************************************
 * The contents of this file are subject to the Mozilla Public License Version 1.1
 * (the "License"); you may not use this file except in compliance with 
 * the License. You may obtain a copy of the License at http://www.mozilla.org/mpl/ 
 * See the License for the specific language governing rights and limitations
 * under the License.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 ************************************************************************************** 
 * Contributor(s): 
 * (Open source contributors should list themselves and their modifications here). */
 // Sergei Leschinski (lsu) 08 aug 2011 - created the file.

#include "stdafx.h"
#include "GlobalSettings.h"

// ****************************************************
//	    get_MinPolygonArea()
// ****************************************************
STDMETHODIMP CGlobalSettings::get_MinPolygonArea(double* retVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	*retVal = m_globalSettings.minPolygonArea;
	return S_OK;
}

// ****************************************************
//	    put_MinPolygonArea()
// ****************************************************
STDMETHODIMP CGlobalSettings::put_MinPolygonArea(double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_globalSettings.minPolygonArea = newVal;
	return S_OK;
}

// ****************************************************
//	    get_MinAreaToPerimeterRatio()
// ****************************************************
STDMETHODIMP CGlobalSettings::get_MinAreaToPerimeterRatio(double* retVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	*retVal = m_globalSettings.minAreaToPerimeterRatio;
	return S_OK;
}

// ****************************************************
//	    put_MinAreaToPerimeterRatio()
// ****************************************************
STDMETHODIMP CGlobalSettings::put_MinAreaToPerimeterRatio(double newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_globalSettings.minAreaToPerimeterRatio = newVal;
	return S_OK;
}

// ****************************************************
//	    get_ClipperGcsMultiplicationFactor()
// ****************************************************
STDMETHODIMP CGlobalSettings::get_ClipperGcsMultiplicationFactor(DOUBLE* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*pVal = m_globalSettings.clipperGcsMultiplicationFactor;
	return S_OK;
}

// ****************************************************
//	    put_ClipperGcsMultiplicationFactor()
// ****************************************************
STDMETHODIMP CGlobalSettings::put_ClipperGcsMultiplicationFactor(DOUBLE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_globalSettings.clipperGcsMultiplicationFactor = newVal;
	return S_OK;
}

// ****************************************************
//	    CreatePoint()
// ****************************************************
STDMETHODIMP CGlobalSettings::CreatePoint(IPoint** retVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_factory.pointFactory->CreateInstance (NULL, IID_IPoint, (void**)retVal);
	return S_OK;
}

// ****************************************************
//	    get_ShapefileFastMode()
// ****************************************************
STDMETHODIMP CGlobalSettings::get_ShapefileFastMode(VARIANT_BOOL* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*pVal = m_globalSettings.shapefileFastMode ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

// ****************************************************
//	    put_ShapefileFastMode()
// ****************************************************
STDMETHODIMP CGlobalSettings::put_ShapefileFastMode(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_globalSettings.shapefileFastMode = newVal == VARIANT_FALSE ? false: true;
	return S_OK;
}

// ****************************************************
//	    get_InvalidShapesBufferDistance()
// ****************************************************
STDMETHODIMP CGlobalSettings::get_InvalidShapesBufferDistance(DOUBLE* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*pVal = m_globalSettings.invalidShapesBufferDistance;
	return S_OK;
}

// ****************************************************
//	    put_InvalidShapesBufferDistance()
// ****************************************************
STDMETHODIMP CGlobalSettings::put_InvalidShapesBufferDistance(DOUBLE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_globalSettings.invalidShapesBufferDistance = newVal;
	return S_OK;
}

// ****************************************************
//	    get_ShapefileFastUnion()
// ****************************************************
STDMETHODIMP CGlobalSettings::get_ShapefileFastUnion(VARIANT_BOOL* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*pVal = m_globalSettings.shapefileFastUnion ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

// ****************************************************
//	    put_ShapefileFastUnion()
// ****************************************************
STDMETHODIMP CGlobalSettings::put_ShapefileFastUnion(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_globalSettings.shapefileFastUnion = newVal?true:false;
	return S_OK;
}

#pragma region "Gdal error handling"
// ****************************************************
//	    get_GdalLastErrorNo()
// ****************************************************
STDMETHODIMP CGlobalSettings::get_GdalLastErrorNo(tkGdalError* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int err = CPLGetLastErrorNo();
	if (err < 0 || err >= (int)GdalErrorUndefined)
		err = (int)GdalErrorUndefined;
	*pVal = (tkGdalError)err;
	return S_OK;
}

// ****************************************************
//	    get_GdalLastErrorType()
// ****************************************************
STDMETHODIMP CGlobalSettings::get_GdalLastErrorType(tkGdalErrorType* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	int err = CPLGetLastErrorType();
	if (err < 0 || err >= (int)GdalUndefined)
		err = (int)GdalUndefined;
	*pVal = (tkGdalErrorType)err;
	return S_OK;
}

// ****************************************************
//	    get_GdalLastErrorMsg()
// ****************************************************
STDMETHODIMP CGlobalSettings::get_GdalLastErrorMsg(BSTR* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CString s = CPLGetLastErrorMsg();
	*pVal = A2BSTR(s);
	return S_OK;
}

// ****************************************************
//	    get_GdalReprojectionErrorMsg()
// ****************************************************
STDMETHODIMP CGlobalSettings::get_GdalReprojectionErrorMsg(BSTR* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*pVal = A2BSTR(m_globalSettings.gdalErrorMessage);
	return S_OK;
}

// ****************************************************
//	    ResetGdalError()
// ****************************************************
STDMETHODIMP CGlobalSettings::ResetGdalError(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CPLErrorReset();
	m_globalSettings.gdalErrorMessage = "";
	return S_OK;
}
#pragma endregion

#pragma region Labels

// ****************************************************
//	    get_CompositingQuality()
// ****************************************************
STDMETHODIMP CGlobalSettings::get_LabelsCompositingQuality(tkCompositingQuality* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*pVal = m_globalSettings.labelsCompositingQuality;
	return S_OK;
}

// ****************************************************
//	    put_CompositingQuality()
// ****************************************************
STDMETHODIMP CGlobalSettings::put_LabelsCompositingQuality(tkCompositingQuality newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (newVal >= 0 && newVal <= AssumeLinear)
		m_globalSettings.labelsCompositingQuality = newVal;
	return S_OK;
}

// ****************************************************
//	    get_SmoothingMode()
// ****************************************************
STDMETHODIMP CGlobalSettings::get_LabelsSmoothingMode(tkSmoothingMode* pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	*pVal = m_globalSettings.labelsSmoothingMode;
	return S_OK;
}

// ****************************************************
//	    put_SmoothingMode()
// ****************************************************
STDMETHODIMP CGlobalSettings::put_LabelsSmoothingMode(tkSmoothingMode newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if (newVal >= 0 && newVal <= AntiAlias)
		m_globalSettings.labelsSmoothingMode = newVal;
	return S_OK;
}
#pragma endregion