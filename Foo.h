#ifndef FOO_H
#define FOO_H


class Foo
{
    public:
        Foo();
        virtual ~Foo();
        int Gettest() { return test; }
        void Settest(int val) { test = val; }
    protected:
    private:
        int test;
};

#endif // FOO_H
