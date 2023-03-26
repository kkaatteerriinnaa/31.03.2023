#include <iostream>
#include <string>
#include <vector>

class Component {
public:
    virtual ~Component() {}
    virtual void add(Component* component) {}
    virtual void remove(Component* component) {}
    virtual bool isComposite() const {
        return false;
    }
    virtual double getPrice() const = 0;
    virtual void print() const = 0;
};

class Leaf : public Component {
public:
    Leaf(std::string name, double price)
        : name_(name)
        , price_(price) {}

    double getPrice() const override {
        return price_;
    }

    void print() const override {
        std::cout << name_ << ": " << price_ << std::endl;
    }

private:
    std::string name_;
    double price_;
};

class Composite : public Component {
public:
    ~Composite() override {
        for (auto component : components_) {
            delete component;
        }
    }

    void add(Component* component) override {
        components_.push_back(component);
    }

    void remove(Component* component) override {
        for (auto i = components_.begin(); i != components_.end(); ++i) {
            if (*i == component) {
                components_.erase(i);
                delete component;
                return;
            }
        }
    }

    bool isComposite() const override {
        return true;
    }

    double getPrice() const override {
        double total = 0.0;
        for (const auto& component : components_) {
            total += component->getPrice();
        }
        return total;
    }

    void print() const override {
        std::cout << "Composite (" << components_.size() << "):\n";
        for (const auto& component : components_) {
            component->print();
        }
    }

private:
    std::vector<Component*> components_;
};

void printTotalPrice(const Component& component) {
    std::cout << "Total price: " << component.getPrice() << std::endl;
}

int main() {
    Composite root;

    Composite reception;
    reception.add(new Leaf("Warm color design", 500.0));
    reception.add(new Leaf("Magazine table", 200.0));
    Composite secretary(new Leaf("Secretary desk", 800.0));
    secretary.add(new Leaf("Computer", 1500.0));
    secretary.add(new Leaf("Office supplies", 100.0));
    reception.add(&secretary);
    reception.add(new Leaf("Water cooler", 400.0));

    Composite classroom1;
    classroom1.add(new Leaf("10 desks", 1500.0));
    classroom1.add(new Leaf("Whiteboard", 100.0));
    Composite teacherDesk(new Leaf("Teacher desk", 500.0));
    teacherDesk.add(new Leaf("Computer", 1500.0));
    classroom1.add(&teacherDesk);
    classroom1.add(new Leaf("Mathematician posters", 50.0));

    Composite classroom2;
    Composite blackDesks(new Leaf("20 black desks", 2000.0));
    blackDesks.add(new Leaf("Desks arranged in oval/circle", 300.0));
    classroom2.add(&blackDesks);
    classroom2.add(new Leaf("Whiteboard", 100.0));
    classroom2.add(new Leaf("Soft sofa", 500.0));

    Composite computerLab;
    Composite computerDesks(new Leaf("10 computer desks", 3000.0));
    Composite computer(new Leaf("Computer", 1500.0));
    computer.add(new Leaf("2.2 GHz processor", 500.0));
    computer.add(new Leaf("80 GB hard", 1000.0));
    computer.add(new Leaf("8 GB RAM", 200.0));
    computerDesks.add(&computer);
    computerLab.add(&computerDesks);
    computerLab.add(new Leaf("Whiteboard", 100.0));

    root.add(&reception);
    root.add(&classroom1);
    root.add(&classroom2);
    root.add(&computerLab);

    root.print();

    printTotalPrice(root);

    return 0;
}