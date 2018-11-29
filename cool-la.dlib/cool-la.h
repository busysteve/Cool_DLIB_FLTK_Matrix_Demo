
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>
#include <FL/fl_draw.H>
#include <math.h>
#include <vector>
//#include "la.h"
#include <dlib/matrix.h>
#include <thread>
#include <chrono>


#define PI	3.14159265358979323846

using namespace dlib;
using namespace std;


class Cool : public Fl_Double_Window
{
	double m_iZRot;
	double m_iVRot;
	double m_iHRot;
	double m_iDots;
	double m_mx;
	double m_my;
    matrix<double, 3, 8 >  m_mat;
    matrix<double, 3, 8 >  m_mat2;
    matrix<double, 3, 2000 >  m_dust;

	static void showoff( Cool *cool )
	{

		while(true)
		{
			for( int r=0; r < 360; r++ )
			{
				this_thread::sleep_for( chrono::milliseconds(400) );

				cool->SetVRot( 120 - 60 * (sin(r / PI * 180.0) ) );
				cool->SetHRot( (double)((int)( r ) % 360) );
		
				Fl::lock();
				Fl::redraw();
				Fl::awake();
				Fl::unlock();
			}
		}
	}

	thread  thx; //( void(*), Cool* );

    //std::vector<la::la_vector<double> > m_vecs;
    //std::vector< std::vector<double> > m_vecs;
    //std::vector< std::vector<double> > m_vecs;
	
public:
	Cool( int x, int y, int w, int h );
	
	virtual void draw();
	
	void SetZRot( int iZRot );
	
	void SetVRot( int iVRot );

	void SetHRot( int iHRot );

	void SetDots( int iDots );
	
	double GetVRot();

	double GetHRot();
	
	double GetZRot();
	
	virtual int handle( int e );

};
