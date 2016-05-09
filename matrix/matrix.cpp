#include <vector>
#include <list>
#include <iostream>
#include <cmath>

#define PI 3.14159265

#define X_COORD 0
#define Y_COORD 1
#define Z_COORD 2

#define DEBUG

using namespace std;

class Coord
{
    public:
    float coord[3];
};


class Col3D
{
    public:
    float col[4];


    Col3D()
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            col[i] = 0;
        }
    }

    void normalize()
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            col[i] = col[i]/col[3];
        }
    }
};

class Matrix3D
{

    public:
    float matrix[4][4];



    void reset()
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            for( int j = 0 ; j < 4 ; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }

    Matrix3D()
    {
        reset();
    }

    void make_identity()
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            reset();
            matrix[i][i] = 1;
        }
    }

    Matrix3D multMatrix( Matrix3D m3d )
    {
        Matrix3D prod;
        for(int i = 0 ; i < 4 ; i++)
        {
            for( int j = 0 ; j < 4 ; j++)
            {
                float sum = 0;
                for (int k  = 0 ; k < 4 ; k++)
                {
                    sum += matrix[i][k]*m3d.matrix[k][j];
                    cout << matrix[i][k] << " " << m3d.matrix[k][j] << endl;
                }
                prod.matrix[i][j]= sum;

            }
        }

        return prod;
    }


    Col3D multCol( Col3D c3d)
    {
        Col3D prod;

        for(int i = 0 ; i < 4 ; i++)
        {
            float sum = 0;
            for (int k  = 0 ; k < 4 ; k++)
            {
                sum += c3d.col[k]*matrix[i][k];
                #ifdef DEBUG
                cout << matrix[i][k] << " " << c3d.col[k] << endl;
                #endif
            }
            #ifdef DEBUG
            cout << "sum " << sum << endl;
            #endif
            prod.col[i]= sum;
        }

        return prod;
    }


};


class Transformations
{

    void general_transform(Matrix3D& mat , Coord& crd)
    {

            #ifdef DEBUG
            cout << "input " << crd.coord[X_COORD] << " " << crd.coord[Y_COORD]<< " " << crd.coord[Z_COORD] << endl;
            #endif
            //create a col
            Col3D c;

            c.col[0] = crd.coord[X_COORD];
            c.col[1] = crd.coord[Y_COORD];
            c.col[2] = crd.coord[Z_COORD];

            c.col[3] = 1;

            //multiply with matrix
            Col3D final_col = mat.multCol(c);

            //normalize - not useful in case of most
            //final_col.normalize();
            //get coord
            crd.coord[X_COORD] = final_col.col[0];
            crd.coord[Y_COORD] = final_col.col[1];
            crd.coord[Z_COORD] = final_col.col[2];

            #ifdef DEBUG
            cout << "output " << crd.coord[X_COORD] << " " << crd.coord[Y_COORD]<< " " << crd.coord[Z_COORD] << endl;
            #endif

    }


    public:

    vector<Coord> translate_list(vector< Coord > list , float tx , float ty , float tz)
    {

        vector<Coord> final_list;
        //translate coord
        Matrix3D tr_mat;


        //translation matrix
        tr_mat.make_identity();
        tr_mat.matrix[0][3] = tx;
        tr_mat.matrix[1][3] = ty;
        tr_mat.matrix[2][3] = tz;


        for( int i = 0 ; i < list.size() ; i++)
        {

            Coord crd = list[i];
            general_transform(tr_mat , crd);

            //push in final list
            final_list.push_back(crd);

        }

        return final_list;

    }


    vector<Coord> scale_list(vector< Coord > list , float sx , float sy , float sz)
    {

        vector<Coord> final_list;
        //translate coord
        Matrix3D tr_mat;


        //translation matrix
        tr_mat.make_identity();
        tr_mat.matrix[0][0] = sx;
        tr_mat.matrix[1][1] = sy;
        tr_mat.matrix[2][2] = sz;


        for( int i = 0 ; i < list.size() ; i++)
        {

            Coord crd = list[i];
            general_transform(tr_mat , crd);

            //push in final list
            final_list.push_back(crd);

        }

        return final_list;

    }


    vector<Coord> rotate_x_list(vector< Coord > list , float alpha)
    {

        vector<Coord> final_list;
        //translate coord
        Matrix3D tr_mat;


        //translation matrix
        tr_mat.make_identity();
        tr_mat.matrix[1][1] = cos (alpha*PI/180);
        tr_mat.matrix[2][2] = cos (alpha*PI/180);
        tr_mat.matrix[2][1] = sin (alpha*PI/180);
        tr_mat.matrix[1][2] = -sin (alpha*PI/180);

        for( int i = 0 ; i < list.size() ; i++)
        {

            Coord crd = list[i];
            general_transform(tr_mat , crd);

            //push in final list
            final_list.push_back(crd);

        }

        return final_list;

    }

    vector<Coord> rotate_y_list(vector< Coord > list , float alpha)
    {

        vector<Coord> final_list;
        //translate coord
        Matrix3D tr_mat;


        //translation matrix
        tr_mat.make_identity();
        tr_mat.matrix[0][0] = cos (alpha*PI/180);
        tr_mat.matrix[2][2] = cos (alpha*PI/180);
        tr_mat.matrix[0][2] = sin (alpha*PI/180);
        tr_mat.matrix[2][0] = -sin (alpha*PI/180);

        for( int i = 0 ; i < list.size() ; i++)
        {

            Coord crd = list[i];
            general_transform(tr_mat , crd);

            //push in final list
            final_list.push_back(crd);

        }

        return final_list;

    }


    vector<Coord> rotate_z_list(vector< Coord > list , float alpha)
    {

        vector<Coord> final_list;
        //translate coord
        Matrix3D tr_mat;


        //translation matrix
        tr_mat.make_identity();
        tr_mat.matrix[0][0] = cos (alpha*PI/180);
        tr_mat.matrix[1][1] = cos (alpha*PI/180);
        tr_mat.matrix[1][0] = sin (alpha*PI/180);
        tr_mat.matrix[0][1] = -sin (alpha*PI/180);

        for( int i = 0 ; i < list.size() ; i++)
        {

            Coord crd = list[i];
            general_transform(tr_mat , crd);

            //push in final list
            final_list.push_back(crd);

        }

        return final_list;

    }



};


int main()
{

    vector<Coord> list;
    Coord c;

    //create three pnts

    c.coord[X_COORD] = 0;
    c.coord[Y_COORD] = 0;
    c.coord[Z_COORD] = 0;
    list.push_back(c);

    c.coord[X_COORD] = 0;
    c.coord[Y_COORD] = 1;
    c.coord[Z_COORD] = 0;
    list.push_back(c);

    c.coord[X_COORD] = 1;
    c.coord[Y_COORD] = 0;
    c.coord[Z_COORD] = 0;
    list.push_back(c);



    //transformation instance
    Transformations ts;

    //transform
    vector<Coord> out_list = ts.translate_list(list , 1,1,1);

    //print list
    for(int i = 0 ; i < out_list.size() ; i++)
    {
        cout << out_list[i].coord[X_COORD] << "  " << out_list[i].coord[Y_COORD] << "  " << out_list[i].coord[Z_COORD] << endl;
    }

}
