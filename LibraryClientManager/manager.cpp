#include "manager.hpp"
#include <iostream>
#include <algorithm>

MemberManager::MemberManager()
    : nextId(1)
{
}

// ID로 포인터 반환, 못 찾으면 nullptr
Member* MemberManager::findById(int id) {
    for (auto& m : members) {
        if (m.getId() == id) return &m;
    }
    return nullptr;
}

void MemberManager::addMember() {
    std::string name, phone, email, address;
    std::cout << "이름: ";   std::getline(std::cin, name);
    std::cout << "전화: ";   std::getline(std::cin, phone);
    std::cout << "이메일: "; std::getline(std::cin, email);
    std::cout << "주소: ";   std::getline(std::cin, address);

    members.emplace_back(nextId, name, phone, email, address);
    std::cout << "회원 등록 완료 (ID=" << nextId << ")\n";
    nextId++;
}

void MemberManager::removeMember() {
    std::cout << "삭제할 회원 ID: ";
    int id; std::cin >> id; std::cin.ignore();
    auto it = std::remove_if(members.begin(), members.end(),
        [&](const Member& m) { return m.getId() == id; });
    if (it != members.end()) {
        members.erase(it, members.end());
        std::cout << "ID " << id << " 회원 삭제됨\n";
    }
    else {
        std::cout << "회원이 없습니다.\n";
    }
}

void MemberManager::showAllMembers() const {
    if (members.empty()) {
        std::cout << "등록된 회원이 없습니다.\n";
        return;
    }
    for (const auto& m : members) {
        m.printSummary();
    }
}

void MemberManager::showMemberDetail() const {
    std::cout << "상세조회할 회원 ID: ";
    int id; std::cin >> id; std::cin.ignore();
    auto* m = const_cast<MemberManager*>(this)->findById(id);
    if (m) m->printDetail();
    else   std::cout << "회원이 없습니다.\n";
}

void MemberManager::borrowBook() {
    std::cout << "대출할 회원 ID: ";
    int id; std::cin >> id; std::cin.ignore();
    std::cout << "반납 예정일 (YYYY-MM-DD): ";
    std::string due; std::getline(std::cin, due);
    if (auto* m = findById(id)) {
        m->borrowBook(due);
        std::cout << "대출 처리 완료\n";
    }
    else {
        std::cout << "회원이 없습니다.\n";
    }
}

void MemberManager::returnBook() {
    std::cout << "반납할 회원 ID: ";
    int id; std::cin >> id; std::cin.ignore();
    if (auto* m = findById(id)) {
        m->returnBook();
        std::cout << "반납 처리 완료\n";
    }
    else {
        std::cout << "회원이 없습니다.\n";
    }
}

void MemberManager::showOverdueMembers() const {
    bool any = false;
    for (const auto& m : members) {
        if (m.getOverdue()) {
            m.printSummary();
            any = true;
        }
    }
    if (!any) std::cout << "연체 중인 회원이 없습니다.\n";
}

void MemberManager::showByGrade() const {
    std::cout << "조회할 등급 (0=Bronze,1=Silver,2=Gold,3=Platinum): ";
    int g; std::cin >> g; std::cin.ignore();
    Grade grade = static_cast<Grade>(g);
    bool any = false;
    for (const auto& m : members) {
        if (m.getGrade() == grade) {
            m.printSummary();
            any = true;
        }
    }
    if (!any) std::cout << "해당 등급 회원이 없습니다.\n";
}
// 연체 벌금 납부
void MemberManager::collectFine() {
    std::cout << "벌금 납부할 회원 ID: ";
    int id; std::cin >> id; std::cin.ignore();
    Member* m = findById(id);
    if (!m) {
        std::cout << "회원이 없습니다.\n";
        return;
    }

    double owed = m->getFineBalance();
    if (owed <= 0.0) {
        std::cout << "벌금이 없습니다.\n";
        return;
    }

    std::cout << "현재 미납 벌금: " << owed << "원\n";
    std::cout << "납부할 금액: ";
    double pay; std::cin >> pay; std::cin.ignore();
    if (pay <= 0 || pay > owed) {
        std::cout << "잘못된 금액입니다.\n";
        return;
    }

    // 벌금 차감
    m->payFine(pay);

    std::cout << "납부 완료. 남은 벌금: " << m->getFineBalance() << "원\n";
}