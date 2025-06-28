// member.hpp
#pragma once

#include <string>
#include <iostream>

enum class Grade { Bronze, Silver, Gold, Platinum };
enum class Role { Admin, Staff, Guest };

class Member {
private:
    int         id;
    std::string name;
    std::string phone;
    std::string email;
    std::string address;

    int         totalBorrowed;
    int         totalReturned;
    int         currentBorrowed;
    std::string dueDate;       // YYYY-MM-DD
    bool        isOverdue;
    double      fineBalance;

    Grade       grade;
    Role        role;
    std::string notes;

    // 내부 헬퍼
    std::string   getTodayString() const;
    void          checkOverdue();
    void          updateGrade();
    static std::string gradeToString(Grade g);

public:
    Member(int id,
        const std::string& name,
        const std::string& phone,
        const std::string& email,
        const std::string& address,
        Role role = Role::Guest);

    // 접근자
    int         getId()           const;
    const std::string& getName()  const;
    Grade       getGrade()        const;
    bool        getOverdue()      const;
    double      getFineBalance()  const;
    Role        getRole()         const;

    // 대출·반납
    void borrowBook(const std::string& newDueDate);
    void returnBook();

    // 벌금
    void applyFine(int daysOverdue);
    void payFine(double amount);

    // 출력
    void printSummary() const;
    void printDetail()  const;
};
