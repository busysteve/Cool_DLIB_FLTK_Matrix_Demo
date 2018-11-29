

//class Cool : public Fl_Double_Window

#include <iostream>
#include "cool-la.h"


//std::vector< la::la_vector<double> > vecs;




double non( double x ) { return ( x ); }

double sinc( double x ) { return (x == 0) ? 1.0 : sin( x ) / x; }
double sincd( double x ) { return sinc( x*PI/180.0 ); }

double nsin( double x ) { return -sin( x ); }
double ncos( double x ) { return -cos( x ); }
double ntan( double x ) { return -tan( x ); }

double sind( double x ) { return sin( x*PI/180.0 ); }
double cosd( double x ) { return cos( x*PI/180.0 ); }
double tand( double x ) { return tan( x*PI/180.0 ); }

double nsind( double x ) { return -sin( x*PI/180.0 ); }
double ncosd( double x ) { return -cos( x*PI/180.0 ); }
double ntand( double x ) { return -tan( x*PI/180.0 ); }


Cool::Cool( int x, int y, int w, int h )
	: Fl_Double_Window( x,y,w,h,0)//, thx( Cool::showoff, this ) 
{

/*
    vecs.push_back( {100, 100, 100} );    // RTF
    vecs.push_back( {100, 100, -100} );   // RTR
    vecs.push_back( {100, -100, 100} );   // RBF
    vecs.push_back( {100, -100, -100} );  // RBR
    vecs.push_back( {-100, 100, 100} );   // LTF
    vecs.push_back( {-100, 100, -100} );  // LTR
    vecs.push_back( {-100, -100, 100} );  // LBF
    vecs.push_back( {-100, -100, -100} ); // LBR
*/

/*
    m_mat = 
     100,    100,    100,
     100,    100,   -100,
     100,   -100,    100,
     100,   -100,   -100,
    -100,    100,    100,
    -100,    100,   -100,
    -100,   -100,    100,
    -100,   -100,   -100;
*/
    m_mat = 
     100,    -100,   -100,     100,    100,   -100,   -100,     100,
     100,     100,   -100,    -100,    100,    100,   -100,    -100,
     100,     100,    100,     100,   -100,   -100,   -100,    -100;

    m_mat2 = 
     20,    -20,   -20,     20,    20,   -20,   -20,     20,
     20,     20,   -20,    -20,    20,    20,   -20,    -20,
     20,     20,    20,     20,   -20,   -20,   -20,    -20;



    for( int i=0; i < m_dust.nc(); i++ )
    {
		//double x = (((double)i ) );
		//double y = (((double)-i ) );
		//double y = ((((double)::rand() / (double)RAND_MAX)/2.0) )*25.0;

		//double z = sincd(::sqrt(::pow(x,2)+::pow(y,2)))*50.0;

		
        //m_dust( 0, i ) = (::rand() % 100) - 50 ;
        //m_dust( 1, i ) = (::rand() % 100) - 50 ;
        //m_dust( 2, i ) = (::rand() % 100) - 50 ;

		double rnd = (double)::rand() / (double)RAND_MAX * 360.0;
		double rnd2 = (double)::rand() / (double)RAND_MAX * 360.0;
		double rnd3 = (double)::rand() / (double)RAND_MAX * 360.0;
		//double rnd4 = (double)::rand() / (double)RAND_MAX * 100.0;
		double radius =  85.0;

        m_dust( 0, i ) = (cosd(rnd) * sind(rnd2)) * radius;
        m_dust( 1, i ) = (sind(rnd) * sind(rnd2)) * radius;
        //m_dust( 2, i ) = (cosd(rnd) * cosd(rnd2) * sind(rnd) * sind(rnd2)) * 100.0;
        m_dust( 2, i ) = (cosd(rnd2) ) /* * sin(rnd3) */ * radius;

    }

	m_iDots = 100;

	//thx.detach();

}

void Cool::SetZRot( int iZRot )
{
	m_iZRot = iZRot;
	this->redraw();
}

void Cool::SetVRot( int iVRot )
{
	m_iVRot = iVRot;
	this->redraw();
}

void Cool::SetHRot( int iHRot )
{
	m_iHRot = iHRot;
	this->redraw();
}

void Cool::SetDots( int iDots )
{
	m_iDots = iDots;
	this->redraw();
}

double Cool::GetZRot()
{
	return m_iZRot;
}

double Cool::GetVRot()
{
	return m_iVRot;
}

double Cool::GetHRot()
{
	return m_iHRot;
}


int Cool::handle( int e )
{
	

	switch( e )
	{
	case FL_PUSH:
		m_mx = Fl::event_x();
		m_my = Fl::event_y();
		return 1;
	case FL_RELEASE:
		return 1;
	case FL_DRAG:
		m_iVRot += (Fl::event_x() - m_mx)*.5;
		m_iHRot += (Fl::event_y() - m_my)*.5;
	
		m_iHRot = m_iHRot > 360 ? (int)m_iHRot%360 : m_iHRot;
		m_iHRot = m_iHRot < 0 ? 360 - ((int)-m_iHRot%360) : m_iHRot;

		m_iVRot = m_iVRot > 360 ? (int)m_iVRot%360 : m_iVRot;
		m_iVRot = m_iVRot < 0 ? 360 - ((int)-m_iVRot%360) : m_iVRot;

		m_iZRot = m_iZRot > 360 ? (int)m_iZRot%360 : m_iZRot;
		m_iZRot = m_iZRot < 0 ? 360 - ((int)-m_iZRot%360) : m_iZRot;

		m_mx = Fl::event_x();
		m_my = Fl::event_y();
		this->redraw();
		return 1;
	default:
		return Fl_Double_Window::handle(e);
	}

}


void Cool::draw()
{

	int r = w() < h() ? w()/2 : h()/2;

    matrix<double, 3, 3> rotx; 
    matrix<double, 3, 3> roty; 
    matrix<double, 3, 3> rotz; 

    rotx = 
        1, 0, 0,
        0, cosd(m_iHRot), sind(m_iHRot),
        0, nsind(m_iHRot), cosd(m_iHRot);              

    roty = 
        cosd(m_iVRot), 0, sind(m_iVRot),
        0, 1, 0,
        nsind(m_iVRot), 0, cosd(m_iVRot);

    rotz = 
        cosd(m_iZRot), nsind(m_iZRot), 0,
        sind(m_iZRot), cosd(m_iZRot),  0,
                   0, 0,             1;


	//for(int b = 1; b < 100; b++ )
	{

		fl_color( FL_BLACK );
		fl_rectf( 0, 0, w(), h() );

		{

			fl_color( FL_GRAY );

            matrix<double> 
            rot = rotx * m_mat2;
            rot = roty * rot;
            rot = rotz * rot;

            fl_line( r+rot(0,0), r+rot(1,0), r+rot(0,1), r+rot(1,1) ); 
            fl_line( r+rot(0,1), r+rot(1,1), r+rot(0,2), r+rot(1,2) ); 
            fl_line( r+rot(0,2), r+rot(1,2), r+rot(0,3), r+rot(1,3) ); 
            fl_line( r+rot(0,3), r+rot(1,3), r+rot(0,0), r+rot(1,0) ); 

            fl_line( r+rot(0,4), r+rot(1,4), r+rot(0,5), r+rot(1,5) ); 
            fl_line( r+rot(0,5), r+rot(1,5), r+rot(0,6), r+rot(1,6) ); 
            fl_line( r+rot(0,6), r+rot(1,6), r+rot(0,7), r+rot(1,7) ); 
            fl_line( r+rot(0,7), r+rot(1,7), r+rot(0,4), r+rot(1,4) ); 

            fl_line( r+rot(0,0), r+rot(1,0), r+rot(0,4), r+rot(1,4) ); 
            fl_line( r+rot(0,1), r+rot(1,1), r+rot(0,5), r+rot(1,5) ); 
            fl_line( r+rot(0,2), r+rot(1,2), r+rot(0,6), r+rot(1,6) ); 
            fl_line( r+rot(0,3), r+rot(1,3), r+rot(0,7), r+rot(1,7) ); 
		}

		{

			fl_color( FL_WHITE );

            matrix<double> 
            rot = rotx * m_mat;
            rot = roty * rot;
            rot = rotz * rot;

            matrix<double> 
            dust_rot = rotx * m_dust;
            dust_rot = roty * dust_rot;
            dust_rot = rotz * dust_rot;

            for( int c=0; c < rot.nc(); c++ )
            {   					
                double x = rot(0,c);
                double y = rot(1,c);
				
				char num[5];
				sprintf( num, "%d", c );
				fl_draw( num, r+x, r+y );
            }

            fl_color( FL_GRAY );
            //for( int d=0; d < m_dust.nc(); d++ )
            for( int d=0; d < m_iDots; d++ )
                fl_point( r+dust_rot(0, d), r+dust_rot(1, d) );
			
			fl_color(fl_rgb_color( 255,255,255 ));
            fl_line( r+rot(0,0), r+rot(1,0), r+rot(0,1), r+rot(1,1) ); 
			fl_color(fl_rgb_color( 255,255,0 ));
            fl_line( r+rot(0,1), r+rot(1,1), r+rot(0,2), r+rot(1,2) ); 
			fl_color(fl_rgb_color( 255,0,255 ));
            fl_line( r+rot(0,2), r+rot(1,2), r+rot(0,3), r+rot(1,3) ); 
			fl_color(fl_rgb_color( 255,0,0 ));
            fl_line( r+rot(0,3), r+rot(1,3), r+rot(0,0), r+rot(1,0) ); 

			fl_color(fl_rgb_color( 0,255,255 ));
            fl_line( r+rot(0,4), r+rot(1,4), r+rot(0,5), r+rot(1,5) ); 
			fl_color(fl_rgb_color( 0,255,0 ));
            fl_line( r+rot(0,5), r+rot(1,5), r+rot(0,6), r+rot(1,6) ); 
			fl_color(fl_rgb_color( 0,0,255 ));
            fl_line( r+rot(0,6), r+rot(1,6), r+rot(0,7), r+rot(1,7) ); 
			fl_color(fl_rgb_color( 128,0,128 ));
            fl_line( r+rot(0,7), r+rot(1,7), r+rot(0,4), r+rot(1,4) ); 

			fl_color(fl_rgb_color( 128,128,128 ));
            fl_line( r+rot(0,0), r+rot(1,0), r+rot(0,4), r+rot(1,4) ); 
			fl_color(fl_rgb_color( 255,0,128 ));
            fl_line( r+rot(0,1), r+rot(1,1), r+rot(0,5), r+rot(1,5) ); 
			fl_color(fl_rgb_color( 128,0,255 ));
            fl_line( r+rot(0,2), r+rot(1,2), r+rot(0,6), r+rot(1,6) ); 
			fl_color(fl_rgb_color( 128,255,128 ));
            fl_line( r+rot(0,3), r+rot(1,3), r+rot(0,7), r+rot(1,7) ); 
		}


	}

	this->do_callback();

	//Fl_Window::draw();
}

