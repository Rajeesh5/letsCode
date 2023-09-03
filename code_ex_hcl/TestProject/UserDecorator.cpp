#include<iostream>

using namespace std;

class Text {    // 1. "lowest common denominator"
public:
    virtual void draw() = 0;
};

class SimpleTextField : public Text {  // 3. "Core" class & "is a"    
public:
    SimpleTextField(int w, int h, string text) :width(w), height(h), m_text(text) {}
    void draw() {
        cout << "Simple text:: " << m_text << endl;
    }
private:
    int width, height;
    string m_text;
};

// 2. 2nd level base class
class TextDecorator : public Text  // 4. "is a" relationship
{
protected:
    Text* m_text; // 4. "has a" relationship
public:
    TextDecorator(Text* text) : m_text(text) {}
    /*virtual*/
    void draw() {
        m_text->draw(); // 5. Delegation
    }
};

class HTextBar : public TextDecorator {
public:
    HTextBar(Text* w) : TextDecorator(w) {}
    virtual void draw() {
        // 7. Delegate to base class and add extra stuff
        m_text->draw();
        cout << "Text with HorizontalBar" << '\n';
    }
};

class VTextBar : public TextDecorator
{
public:
    // 6. Optional embellishment
    VTextBar(Text* w) : TextDecorator(w) {}
    virtual void draw() {
        // 7. Delegate to base class and add extra stuff
        m_text->draw();
        cout << "Text with VerticalBar" << '\n';
    }
};






int main()
{
    // 8. Client has the responsibility to compose desired configurations

    Text* text = new SimpleTextField(50, 30, "Simple Test");
    text = new HTextBar(text);
    text = new VTextBar(text);

    text->draw();

    return 0;
}
