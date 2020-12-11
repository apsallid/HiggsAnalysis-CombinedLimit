//---------------------------------------------------------------------------
#ifndef HiggsAnalysis_CombinedLimit_RooInvPowLinOrd2BinPdf
#define HiggsAnalysis_CombinedLimit_RooInvPowLinOrd2BinPdf
//---------------------------------------------------------------------------
#include "RooAbsPdf.h"
#include "RooConstVar.h"
#include "RooRealProxy.h"
//---------------------------------------------------------------------------
class RooRealVar;
class RooAbsReal;

#include "Riostream.h"
#include "TMath.h"
#include <TH1.h>
#include "Math/SpecFuncMathCore.h"
#include "Math/SpecFuncMathMore.h"
#include "Math/Functor.h"
#include "Math/WrappedFunction.h"
#include "Math/IFunction.h"
#include "Math/Integrator.h"

//---------------------------------------------------------------------------
class RooInvPowLinOrd2BinPdf : public RooAbsPdf
{
public:
   RooInvPowLinOrd2BinPdf() {} ;
   RooInvPowLinOrd2BinPdf(const char *name, const char *title,
		    RooAbsReal& _th1x, RooAbsReal& _p1,	RooAbsReal& _p2, RooAbsReal& _p3, RooAbsReal& _p4);
   RooInvPowLinOrd2BinPdf(const RooInvPowLinOrd2BinPdf& other,
      const char* name = 0);
   void setTH1Binning(TH1* _Hnominal);
   void setAbsTol(double _absTol);
   void setRelTol(double _relTol);
   virtual TObject* clone(const char* newname) const { return new RooInvPowLinOrd2BinPdf(*this,newname); }
   inline virtual ~RooInvPowLinOrd2BinPdf() { }

   Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName=0) const;
   Double_t analyticalIntegral(Int_t code, const char* rangeName=0) const;

protected:   

   RooRealProxy th1x;        // dependent variable
   RooRealProxy p1;       // p1
   RooRealProxy p2;        // p2
   RooRealProxy p3;        // p2
   RooRealProxy p4;        // p2
   Int_t xBins;        // X bins
   Double_t xArray[2000]; // xArray[xBins+1]
   Double_t xMax;        // X max
   Double_t xMin;        // X min
   Double_t relTol;      //relative tolerance for numerical integration
   Double_t absTol;      //absolute tolerance for numerical integration

   Double_t evaluate() const;
private:
   ClassDef(RooInvPowLinOrd2BinPdf,1) // RazorModExpBinPdf function
    
};
//---------------------------------------------------------------------------
#endif

#include "Math/IFunction.h"
#include "Math/IParamFunction.h"
 
class InvPowLinOrd2Function: public ROOT::Math::IParametricFunctionOneDim
{
private:
   const double *pars;
 
public:
   double DoEvalPar(double x,const double* p) const
   {
     double pdf = pow(1+x*p[0],p[1]+p[2]*x+p[3]*x*x);
     return pdf;
   }
   double DoEval(double x) const
   {
     double pdf = pow(1+x*pars[0],pars[1]+pars[2]*x+pars[3]*x*x);
     return pdf;
   }
 
   ROOT::Math::IBaseFunctionOneDim* Clone() const
   {
      return new InvPowLinOrd2Function();
   }
 
   const double* Parameters() const
   {
      return pars;
   }
 
   void SetParameters(const double* p)
   {
      pars = p;
   }
 
   unsigned int NPar() const
   {
      return 4;
   }
};
