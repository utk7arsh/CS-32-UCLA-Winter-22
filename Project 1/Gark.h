//gark.h
#ifndef GARK_
#define GARK_

class Mesa;

class Gark
{
public:
    // Constructor
    Gark(Mesa* mp, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;

    // Mutators
    void move();
    bool getAttacked(int dir);

private:
    Mesa* m_mesa;
    int   m_row;
    int   m_col;
    int   m_health;
};

#endif

