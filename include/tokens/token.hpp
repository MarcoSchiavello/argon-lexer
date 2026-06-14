#pragma once

#include <string>

class Token {
    public:
        virtual ~Token() = default;
        Token(const int id, const std::string& label) {
            m_id=id; 
            m_label=label; 
        }

        [[nodiscard]]  int getId() const { return m_id; }
        [[nodiscard]]  std::string getLabel() const { return m_label; }
        virtual std::string toString() {  return "<" + std::to_string(m_id) + "," + m_label + ">";}

    private:
        int m_id;
        std::string m_label;
};