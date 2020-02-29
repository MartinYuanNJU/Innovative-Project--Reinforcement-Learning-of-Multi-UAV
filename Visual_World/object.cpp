#include "object.h"

void Object::reset(Pos pos)
{
    assert(pos.row>=0&&pos.row<WORLD_SIZE&&pos.col>=0&&pos.col<WORLD_SIZE);
    this->pos=pos;
    detected=false;
}

bool Object::step_forward(int direction)
{
    if(pos.row<20) //leftside
    {
        if(direction==1) //front
        {
            if(pos.col==21)
                return false;
            else
            {
                pos.col--;
                return true;
            }
        }
        else if(direction==2) //back
        {
            if(pos.col==28)
                return false;
            else
            {
                pos.col++;
                return true;
            }
        }
        else if(direction==3) //left
        {
            if(pos.row==0)
                return false;
            else
            {
                pos.row--;
                return true;
            }
        }
        else //right
        {
            if(pos.row==19)
                return false;
            else
            {
                pos.row++;
                return true;
            }
        }
    }
    else //rightside
    {
        if(direction==1) //front
        {
            if(pos.col==21)
                return false;
            else
            {
                pos.col--;
                return true;
            }
        }
        else if(direction==2) //back
        {
            if(pos.col==28)
                return false;
            else
            {
                pos.col++;
                return true;
            }
        }
        else if(direction==3) //left
        {
            if(pos.row==30)
                return false;
            else
            {
                pos.row--;
                return true;
            }
        }
        else //right
        {
            if(pos.row==49)
                return false;
            else
            {
                pos.row++;
                return true;
            }
        }
    }
    return true;
}

void Object::update()
{
    bool ok=false;
    while(!ok)
    {
        int random=random_(4);
        ok=step_forward(random);
    }
}

Pos Object::get_pos()
{
    return pos;
}

bool Object::detect(Pos uav_pos)
{
    if(detected==true)
        return false;
    else if(uav_pos.row==pos.row&&uav_pos.col==pos.col)
    {
        detected=true;
        return true;
    }
    else
        return false;
}
