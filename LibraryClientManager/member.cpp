#define _CRT_SECURE_NO_WARNINGS

// member.cpp
#include "member.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

namespace {
    constexpr double FINE_RATE = 500.0;  // per day
    int daysBetween(const std::string& start, const std::string& end) {
        std::tm tmStart{};
        std::tm tmEnd{};
        std::istringstream ssStart(start);
        ssStart >> std::get_time(&tmStart, "%Y-%m-%d");
        std::istringstream ssEnd(end);
        ssEnd >> std::get_time(&tmEnd, "%Y-%m-%d");
        std::time_t timeStart = std::mktime(&tmStart);
        std::time_t timeEnd = std::mktime(&tmEnd);
        if (timeStart == -1 || timeEnd == -1) return 0;
        double diff = std::difftime(timeEnd, timeStart);
        return static_cast<int>(diff / (60 * 60 * 24));
    }
}

// -----------------------------
    if (currentBorrowed > 0 && !dueDate.empty()) {
        std::string today = getTodayString();
        if (today > dueDate) {
            int days = daysBetween(dueDate, today);
            if (days > 0) applyFine(days);
            isOverdue = true;
            return;
        }
    isOverdue = false;
    Role role)
    : id(id)
    , name(name)
    , phone(phone)
    , email(email)
    , address(address)
    , totalBorrowed(0)
    , totalReturned(0)
    , currentBorrowed(0)
    , dueDate("")
    , isOverdue(false)
    , fineBalance(0.0)
    , grade(Grade::Bronze)
    , role(role)
    , notes("")
{
}

// -----------------------------
// 내부 헬퍼
std::string Member::getTodayString() const {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

void Member::checkOverdue() {
    if (currentBorrowed > 0 && getTodayString() > dueDate) {
        isOverdue = true;
        // TODO: 실제 연체 일수 계산해서 applyFine() 호출
    }
    else {
        isOverdue = false;
    }
}

void Member::updateGrade() {
    if (totalReturned >= 50) grade = Grade::Platinum;
    else if (totalReturned >= 30) grade = Grade::Gold;
    else if (totalReturned >= 10) grade = Grade::Silver;
    else                          grade = Grade::Bronze;
}

std::string Member::gradeToString(Grade g) {
    switch (g) {
    case Grade::Bronze:   return "Bronze";
    case Grade::Silver:   return "Silver";
    case Grade::Gold:     return "Gold";
    case Grade::Platinum: return "Platinum";
    }
    return "Unknown";
}

// -----------------------------
// 접근자
int Member::getId()          const { return id; }
const std::string& Member::getName() const { return name; }
Grade Member::getGrade()     const { return grade; }
bool Member::getOverdue()    const { return isOverdue; }
double Member::getFineBalance() const { return fineBalance; }
Role Member::getRole()       const { return role; }

// -----------------------------
// 대출·반납
void Member::borrowBook(const std::string& newDueDate) {
    totalBorrowed++;
    currentBorrowed++;
    dueDate = newDueDate;
    checkOverdue();
    updateGrade();
}

void Member::returnBook() {
    if (currentBorrowed > 0) {
        totalReturned++;
        currentBorrowed--;
        checkOverdue();
        updateGrade();
    }
}

// -----------------------------
// 벌금
void Member::applyFine(int daysOverdue) {
    fineBalance += daysOverdue * FINE_RATE;
    isOverdue = true;
    // payFine: 실제 납부 금액(amount 원)을 벌금잔액에서 차감
   
}
void Member::payFine(double amount) {
    fineBalance -= amount;
    if (fineBalance < 0.0) fineBalance = 0.0;

}

// -----------------------------
// 출력
void Member::printSummary() const {
    std::cout
        << id << " | " << name
        << " | 등급: " << gradeToString(grade)
        << " | 대출중: " << currentBorrowed
        << (isOverdue ? " (연체!)" : "")
        << " | 벌금: " << fineBalance
        << "\n";
}

void Member::printDetail() const {
    std::cout
        << "ID: " << id
        << "\n이름: " << name
        << "\n연락처: " << phone
        << "\n이메일: " << email
        << "\n주소: " << address
        << "\n총대출: " << totalBorrowed
        << "\n총반납: " << totalReturned
        << "\n현재대출: " << currentBorrowed
        << "\n반납예정: " << dueDate
        << "\n연체여부: " << (isOverdue ? "예" : "아니오")
        << "\n벌금잔액: " << fineBalance
        << "\n등급: " << gradeToString(grade)
        << "\n메모: " << notes
        << "\n\n";
}
