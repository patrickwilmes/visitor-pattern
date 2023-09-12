#include <iostream>
#include <string>

// Simple Document Visitor
// -----------------------
class Document;

class DispatchingPage;

class Teaser;

class DocumentVisitor {
public:
    virtual void visit(Document &doc) = 0;

    virtual void visit(DispatchingPage &page) = 0;

    virtual void visit(Teaser &teaser) = 0;
};

class Document {
public:
    virtual void accept(DocumentVisitor &visitor) = 0;

    [[nodiscard]] std::string title() const {
        return _title;
    }

    [[nodiscard]] std::string content() const {
        return _content;
    }

    void title(const std::string &title) {
        _title = title;
    }

    void content(const std::string &content) {
        _content = content;
    }

private:
    std::string _title;
    std::string _content;
};

class DispatchingPage : public Document {
public:
    void accept(DocumentVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class Teaser : public Document {
public:
    void accept(DocumentVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class DocumentPrinter : public DocumentVisitor {
public:
    void visit(Document &doc) override {
        std::cout << doc.content() << std::endl;
    }

    void visit(DispatchingPage &page) override {
        std::cout << page.content() << std::endl;
    }

    void visit(Teaser &teaser) override {
        std::cout << teaser.content() << std::endl;
    }
};

class DocumentTitlePrinter : public DocumentVisitor {
public:
    void visit(Document &doc) override {
        std::cout << doc.title() << std::endl;
    }

    void visit(DispatchingPage &page) override {
        std::cout << page.title() << std::endl;
    }

    void visit(Teaser &teaser) override {
        std::cout << teaser.title() << std::endl;
    }
};

// -----------------------

// Visitor with a return value
// -----------------------
class Food;

class Banana;

class FoodVisitor {
public:
    virtual float visit(Food &food) = 0;
};

class Food {
public:
    virtual float accept(FoodVisitor &visitor) = 0;

    void price_per_kg(float price_per_kg) {
        _price_per_kg = price_per_kg;
    }

    void weight(float weight) {
        _weight = weight;
    }

    [[nodiscard]] float weight() const {
        return _weight;
    }


    [[nodiscard]] float price_per_kg() const {
        return _price_per_kg;
    }

private:
    float _price_per_kg = 0;
    float _weight = 0;
};

class Banana : public Food {
public:
    float accept(FoodVisitor &visitor) override {
        return visitor.visit(*this);
    }
};

class FoodPriceVisitor : public FoodVisitor {
public:
    float visit(Food &food) override {
        return food.price_per_kg() * food.weight();
    }
};
// -----------------------

int main() {
    DispatchingPage page;
    page.title("Page title");
    page.content("Page content");
    DocumentTitlePrinter titlePrinter;
    page.accept(titlePrinter);

    Banana banana;
    banana.price_per_kg(1.5);
    banana.weight(0.5);
    FoodPriceVisitor priceVisitor;
    std::cout << banana.accept(priceVisitor) << std::endl;
    return 0;
}
