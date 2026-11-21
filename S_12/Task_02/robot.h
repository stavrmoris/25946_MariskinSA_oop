#pragma once

/** @file robot.h
 * @brief последовательная иерархия роботов для демонстрации полиморфизма
 */

#include <string>

/** @brief абстрактный робот с именем и общим интерфейсом передвижения */
class Robot {
private:
    std::string name_; ///< имя экземпляра

public:
    /** @brief сохраняет имя робота
     * @param name непустое имя
     * @throws std::invalid_argument если имя пустое или состоит из пробелов
     */
    explicit Robot(const std::string& name);
    /** @brief позволяет безопасно уничтожать наследников через указатель Robot */
    virtual ~Robot();
    /** @brief возвращает имя робота
     * @return ссылка на имя, действующая в течение жизни робота
     */
    const std::string& getName() const;
    /** @brief показывает статический выбор невиртуального метода
     * @return название базового класса Robot
     */
    const char* getType() const noexcept;
    /** @brief показывает способ передвижения конкретного вида робота
     * @details чистая виртуальная функция должна быть реализована наследником
     */
    virtual void move() = 0;
};

/** @brief квадропедальный робот, реализующий передвижение на четырёх ногах */
class QuadrupedRobot : public Robot {
public:
    /** @brief создаёт квадропедального робота
     * @param name непустое имя
     * @throws std::invalid_argument если имя некорректно
     */
    explicit QuadrupedRobot(const std::string& name);
    /** @brief уничтожает квадропедальную часть */
    ~QuadrupedRobot() override;
    /** @brief показывает передвижение на четырёх ногах */
    void move() override;
    /** @brief показывает скрытие невиртуального метода
     * @return название класса QuadrupedRobot
     */
    const char* getType() const noexcept;
};

/** @brief грузовой квадропедальный робот с массой перевозимого груза */
class CargoRobot : public QuadrupedRobot {
private:
    double cargo_weight_; ///< масса груза в килограммах

public:
    /** @brief создаёт грузового робота
     * @param name непустое имя
     * @param cargo_weight конечная неотрицательная масса в килограммах
     * @throws std::invalid_argument если имя или масса некорректны
     */
    CargoRobot(const std::string& name, double cargo_weight);
    /** @brief уничтожает грузовую часть */
    ~CargoRobot() override;
    /** @brief показывает передвижение с грузом */
    void move() override;
    /** @brief возвращает массу груза
     * @return масса в килограммах
     */
    double getCargoWeight() const;
    /** @brief показывает скрытие невиртуального метода
     * @return название класса CargoRobot
     */
    const char* getType() const noexcept;
};

/** @brief автономный грузовой робот, завершающий последовательную иерархию */
class AutonomousCargoRobot final : public CargoRobot {
private:
    double autonomous_range_; ///< доступный автономный запас хода в километрах

public:
    /** @brief создаёт автономного грузового робота
     * @param name непустое имя
     * @param cargo_weight конечная неотрицательная масса в килограммах
     * @param autonomous_range конечный неотрицательный запас хода в километрах
     * @throws std::invalid_argument если хотя бы один параметр некорректен
     */
    AutonomousCargoRobot(const std::string& name, double cargo_weight, double autonomous_range);
    /** @brief уничтожает автономную часть */
    ~AutonomousCargoRobot() override;
    /** @brief показывает автономную перевозку или управляемый режим при нулевом запасе
     * @details демонстрация выводит способ передвижения и не расходует запас хода
     */
    void move() override;
    /** @brief возвращает автономный запас хода
     * @return запас хода в километрах
     */
    double getAutonomousRange() const;
    /** @brief показывает скрытие невиртуального метода
     * @return название класса AutonomousCargoRobot
     */
    const char* getType() const noexcept;
};
