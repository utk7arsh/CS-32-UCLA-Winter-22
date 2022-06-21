//Your declarationsand implementations would go here
class Sport {
public:
    Sport(string n) {
        s_name = n;
    }
    string name() const { return s_name; }
    virtual string icon() const = 0;
    virtual bool isOutdoor() const { return true; }
    virtual ~Sport() {}

private:
    string s_name;
};

class Snowboarding : public Sport {
public:
    Snowboarding(string n) : Sport(n) {}
    virtual string icon() const { return "a descending snowboarder"; }
    virtual ~Snowboarding() { cout << "Destroying the Snowboarding object named " << this->name() << "." << endl; }
};

class Biathlon : public Sport {
public:
    Biathlon(string n, double dist) : Sport(n) { b_dist = dist; }
    virtual string icon() const { return "a skier with a rifle"; }
    virtual ~Biathlon() { cout << "Destroying the Biathlon object named " << this->name() << ", distance " << b_dist << " km." << endl; }

private:
    double b_dist;
};

class FigureSkating : public Sport {
public:
    FigureSkating(string n) :Sport(n) {}
    virtual string icon() const { return "a skater in the Biellmann position"; }
    virtual bool isOutdoor() const { return false; }
    virtual ~FigureSkating() { cout << "Destroying the FigureSkating object named " << this->name() << "." << endl; }
};