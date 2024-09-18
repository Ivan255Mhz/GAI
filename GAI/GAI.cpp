#include <iostream>
#include <string>
#include <vector>

struct Violation {
    std::string violation;
    double fine;
};

struct Node {
    std::string carNumber;
    std::vector<Violation> violations;
    Node* left;
    Node* right;

    Node(std::string number) : carNumber(number), left(nullptr), right(nullptr) {}
};

class GaiDatabase {
private:
    Node* root;

    void insert(Node* node, std::string carNumber, Violation violation) {
        if (carNumber < node->carNumber) {
            if (node->left == nullptr) {
                node->left = new Node(carNumber);
                node->left->violations.push_back(violation);
            }
            else {
                insert(node->left, carNumber, violation);
            }
        }
        else if (carNumber > node->carNumber) {
            if (node->right == nullptr) {
                node->right = new Node(carNumber);
                node->right->violations.push_back(violation);
            }
            else {
                insert(node->right, carNumber, violation);
            }
        }
        else {
            node->violations.push_back(violation);
        }
    }

    void printDatabase(Node* node) {
        if (node == nullptr) {
            return;
        }

        printDatabase(node->left);
        std::cout << "Car Number: " << node->carNumber << std::endl;
        for (const auto& violation : node->violations) {
            std::cout << "Violation: " << violation.violation << ", Fine: " << violation.fine << std::endl;
        }
        std::cout << std::endl;
        printDatabase(node->right);
    }

    void printByNumber(Node* node, std::string carNumber) {
        if (node == nullptr) {
            return;
        }

        if (carNumber < node->carNumber) {
            printByNumber(node->left, carNumber);
        }
        else if (carNumber > node->carNumber) {
            printByNumber(node->right, carNumber);
        }
        else {
            std::cout << "Car Number: " << node->carNumber << std::endl;
            for (const auto& violation : node->violations) {
                std::cout << "Violation: " << violation.violation << ", Fine: " << violation.fine << std::endl;
            }
            std::cout << std::endl;
        }
    }

    void printByRange(Node* node, std::string minNumber, std::string maxNumber) {
        if (node == nullptr) {
            return;
        }

        if (node->carNumber >= minNumber && node->carNumber <= maxNumber) {
            std::cout << "Car Number: " << node->carNumber << std::endl;
            for (const auto& violation : node->violations) {
                std::cout << "Violation: " << violation.violation << ", Fine: " << violation.fine << std::endl;
            }
            std::cout << std::endl;
        }

        if (node->carNumber < maxNumber) {
            printByRange(node->left, minNumber, maxNumber);
        }
        if (node->carNumber > minNumber) {
            printByRange(node->right, minNumber, maxNumber);
        }
    }

public:
    GaiDatabase() : root(nullptr) {}

    void addViolation(std::string carNumber, std::string violation, double fine) {
        Violation newViolation = { violation, fine };
        if (root == nullptr) {
            root = new Node(carNumber);
            root->violations.push_back(newViolation);
        }
        else {
            insert(root, carNumber, newViolation);
        }
    }

    void printFullDatabase() {
        printDatabase(root);
    }

    void printByCarNumber(std::string carNumber) {
        printByNumber(root, carNumber);
    }

    void printByNumberRange(std::string minNumber, std::string maxNumber) {
        printByRange(root, minNumber, maxNumber);
    }
};

int main() {
    GaiDatabase database;

    database.addViolation("ABC123", "Speeding", 100.0);
    database.addViolation("DEF456", "Parking Violation", 50.0);
    database.addViolation("ABC123", "Running Red Light", 200.0);
    database.addViolation("GHI789", "Expired Registration", 75.0);

    std::cout << "Full Database:" << std::endl;
    database.printFullDatabase();

    std::cout << "Violations for Car Number ABC123:" << std::endl;
    database.printByCarNumber("ABC123");

    std::cout << "Violations for Car Numbers between DEF and HIJ:" << std::endl;
    database.printByNumberRange("DEF", "HIJ");

    return 0;
}
