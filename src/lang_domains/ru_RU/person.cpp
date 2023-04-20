////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2023 Vladislav Trifochkin
//
// This file is part of `lorem-lib`.
//
// Changelog:
//      2023.04.20 Initial version.
////////////////////////////////////////////////////////////////////////////////
#include "../../person_impl.hpp"
#include "pfs/fmt.hpp"
#include <array>

namespace details {

constexpr const char * male_first_name[] = {
      "Абрам", "Август", "Адам", "Адриан", "Аким", "Александр", "Алексей"
    , "Альберт", "Ананий", "Анатолий", "Андрей", "Антон", "Антонин", "Аполлон"
    , "Аркадий", "Арсений", "Артемий", "Артур", "Артём", "Афанасий", "Богдан"
    , "Болеслав", "Борис", "Бронислав", "Вадим", "Валентин", "Валериан"
    , "Валерий", "Василий", "Вениамин", "Викентий", "Виктор", "Виль", "Виталий"
    , "Витольд", "Влад", "Владимир", "Владислав", "Владлен", "Всеволод"
    , "Вячеслав", "Гавриил", "Гарри", "Геннадий", "Георгий", "Герасим"
    , "Герман", "Глеб", "Гордей", "Григорий", "Давид", "Дан", "Даниил"
    , "Данила", "Денис", "Дмитрий", "Добрыня", "Донат", "Евгений", "Егор"
    , "Ефим", "Захар", "Иван", "Игнат", "Игнатий", "Игорь", "Илларион", "Илья"
    , "Иммануил", "Иннокентий", "Иосиф", "Ираклий", "Кирилл", "Клим"
    , "Константин", "Кузьма", "Лаврентий", "Лев", "Леонид", "Макар", "Максим"
    , "Марат", "Марк", "Матвей", "Милан", "Мирослав", "Михаил", "Назар"
    , "Нестор", "Никита", "Никодим", "Николай", "Олег", "Павел", "Платон"
    , "Прохор", "Пётр", "Радислав", "Рафаил", "Роберт", "Родион", "Роман"
    , "Ростислав", "Руслан", "Сава", "Савва", "Святослав", "Семён", "Сергей"
    , "Спартак", "Станислав", "Степан", "Стефан", "Тарас", "Тимофей", "Тимур"
    , "Тит", "Трофим", "Феликс", "Филипп", "Фёдор", "Эдуард", "Эрик", "Юлиан"
    , "Юлий", "Юрий", "Яков", "Ян", "Ярослав", "Милан"
};

constexpr const unsigned int male_first_name_size = sizeof(male_first_name)
    / sizeof(male_first_name[0]);

constexpr const char * female_first_name[] = {
      "Александра", "Алина", "Алиса", "Алла", "Альбина", "Алёна", "Анастасия"
    , "Анжелика", "Анна", "Антонина", "Анфиса", "Валентина", "Валерия"
    , "Варвара", "Василиса", "Вера", "Вероника", "Виктория", "Владлена"
    , "Галина", "Дарья", "Диана", "Дина", "Доминика", "Ева", "Евгения"
    , "Екатерина", "Елена", "Елизавета", "Жанна", "Зинаида", "Злата", "Зоя"
    , "Изабелла", "Изольда", "Инга", "Инесса", "Инна", "Ирина", "Искра"
    , "Капитолина", "Клавдия", "Клара", "Клементина", "Кристина", "Ксения"
    , "Лада", "Лариса", "Лидия", "Лилия", "Любовь", "Людмила", "Люся", "Майя"
    , "Мальвина", "Маргарита", "Марина", "Мария", "Марта", "Надежда", "Наталья"
    , "Нелли", "Ника", "Нина", "Нонна", "Оксана", "Олеся", "Ольга", "Полина"
    , "Рада", "Раиса", "Регина", "Рената", "Розалина", "Светлана", "Софья"
    , "София", "Таисия", "Тамара", "Татьяна", "Ульяна", "Фаина", "Федосья"
    , "Флорентина", "Эльвира", "Эмилия", "Эмма", "Юлия", "Яна", "Ярослава"
};

constexpr const unsigned int female_first_name_size = sizeof(female_first_name)
    / sizeof(female_first_name[0]);

constexpr const char * male_middle_name[] = {
      "Александрович", "Алексеевич", "Андреевич", "Дмитриевич", "Евгеньевич"
    , "Сергеевич", "Иванович", "Фёдорович", "Львович", "Романович"
    , "Владимирович", "Борисович", "Максимович"
};

constexpr const unsigned int male_middle_name_size = sizeof(male_middle_name)
    / sizeof(male_middle_name[0]);

constexpr const char * female_middle_name[] = {
      "Александровна", "Алексеевна", "Андреевна", "Дмитриевна", "Евгеньевна"
    , "Сергеевна", "Ивановна", "Фёдоровна", "Львовна", "Романовна"
    , "Владимировна", "Борисовна", "Максимовна"
};

constexpr const unsigned int female_middle_name_size = sizeof(female_middle_name)
    / sizeof(female_middle_name[0]);

constexpr const char * last_name[] = {
      "Смирнов", "Иванов", "Кузнецов", "Соколов", "Попов", "Лебедев", "Козлов"
    , "Новиков", "Морозов", "Петров", "Волков", "Соловьёв", "Васильев", "Зайцев"
    , "Павлов", "Семёнов", "Голубев", "Виноградов", "Богданов", "Воробьёв"
    , "Фёдоров", "Михайлов", "Беляев", "Тарасов", "Белов", "Комаров", "Орлов"
    , "Киселёв", "Макаров", "Андреев", "Ковалёв", "Ильин", "Гусев", "Титов"
    , "Кузьмин", "Кудрявцев", "Баранов", "Куликов", "Алексеев", "Степанов"
    , "Яковлев", "Сорокин", "Сергеев", "Романов", "Захаров", "Борисов"
    , "Королёв", "Герасимов", "Пономарёв", "Григорьев", "Лазарев", "Медведев"
    , "Ершов", "Никитин", "Соболев", "Рябов", "Поляков", "Цветков", "Данилов"
    , "Жуков", "Фролов", "Журавлёв", "Николаев", "Крылов", "Максимов"
    , "Сидоров", "Осипов", "Белоусов", "Федотов", "Дорофеев", "Егоров"
    , "Матвеев", "Бобров", "Дмитриев", "Калинин", "Анисимов", "Петухов"
    , "Антонов", "Тимофеев", "Никифоров", "Веселов", "Филиппов", "Марков"
    , "Большаков", "Суханов", "Миронов", "Ширяев", "Александров", "Коновалов"
    , "Шестаков", "Казаков", "Ефимов", "Денисов", "Громов", "Фомин", "Давыдов"
    , "Мельников", "Щербаков", "Блинов", "Колесников", "Карпов", "Афанасьев"
    , "Власов", "Маслов", "Исаков", "Тихонов", "Аксёнов", "Гаврилов"
    , "Родионов", "Котов", "Горбунов", "Кудряшов", "Быков", "Зуев", "Третьяков"
    , "Савельев", "Панов", "Рыбаков", "Суворов", "Абрамов", "Воронов", "Мухин"
    , "Архипов", "Трофимов", "Мартынов", "Емельянов", "Горшков", "Чернов"
    , "Овчинников", "Селезнёв", "Панфилов", "Копылов", "Михеев", "Галкин"
    , "Назаров", "Лобанов", "Лукин", "Беляков", "Потапов", "Некрасов", "Хохлов"
    , "Жданов", "Наумов", "Шилов", "Воронцов", "Ермаков", "Дроздов", "Игнатьев"
    , "Савин", "Логинов", "Сафонов", "Капустин", "Кириллов", "Моисеев"
    , "Елисеев", "Кошелев", "Костин", "Горбачёв", "Орехов", "Ефремов", "Исаев"
    , "Евдокимов", "Калашников", "Кабанов", "Носков", "Юдин", "Кулагин"
    , "Лапин", "Прохоров", "Нестеров", "Харитонов", "Агафонов", "Муравьёв"
    , "Ларионов", "Федосеев", "Зимин", "Пахомов", "Шубин", "Игнатов", "Филатов"
    , "Крюков", "Рогов", "Кулаков", "Терентьев", "Молчанов", "Владимиров"
    , "Артемьев", "Гурьев", "Зиновьев", "Гришин", "Кононов", "Дементьев"
    , "Ситников", "Симонов", "Мишин", "Фадеев", "Комиссаров", "Мамонтов"
    , "Носов", "Гуляев", "Шаров", "Устинов", "Вишняков", "Евсеев", "Лаврентьев"
    , "Брагин", "Константинов", "Корнилов", "Авдеев", "Зыков", "Бирюков"
    , "Шарапов", "Никонов", "Щукин", "Дьячков", "Одинцов", "Сазонов", "Якушев"
    , "Красильников", "Гордеев", "Самойлов", "Князев", "Беспалов", "Уваров"
    , "Шашков", "Бобылёв", "Доронин", "Белозёров", "Рожков", "Самсонов"
    , "Мясников", "Лихачёв", "Буров", "Сысоев", "Фомичёв", "Русаков"
    , "Стрелков", "Гущин", "Тетерин", "Колобов", "Субботин", "Фокин", "Блохин"
    , "Селиверстов", "Пестов", "Кондратьев", "Силин", "Меркушев", "Лыткин"
    , "Туров"
};

constexpr const unsigned int last_name_size = sizeof(last_name)
    / sizeof(last_name[0]);

} // namespace details

namespace lorem {

class basic_person_ru_RU: public person::impl
{
public:
    std::string full_name (bool last_is_first) const override
    {
        if (last_is_first)
            return fmt::format("{} {} {}", last_name(-1), first_name(-1), middle_name(-1));

        return fmt::format("{} {} {}", first_name(-1), middle_name(-1), last_name(-1));
    }

    std::string full_name () const override
    {
        return fmt::format("{} {} {}", last_name(-1), first_name(-1), middle_name(-1));
    }
};

class male_person_ru_RU: public basic_person_ru_RU
{
public:
    std::string first_name (int i) const override
    {
        return details::male_first_name[index(details::male_first_name_size, i)];
    }

    std::string middle_name (int i) const override
    {
        return details::male_middle_name[index(details::male_middle_name_size, i)];
    }

    std::string last_name (int i) const override
    {
        return details::last_name[index(details::last_name_size, i)];
    }
};

class female_person_ru_RU: public basic_person_ru_RU
{
public:
    std::string first_name (int i) const override
    {
        return details::female_first_name[index(details::female_first_name_size, i)];
    }

    std::string middle_name (int i) const override
    {
        return details::female_middle_name[index(details::female_middle_name_size, i)];
    }

    std::string last_name (int i) const override
    {
        return details::last_name[index(details::last_name_size, i)] + std::string{"а"};
    }
};

} // namespace lorem

extern "C" lorem::person::impl const * person_ru_RU (lorem::gender g)
{
    static const lorem::male_person_ru_RU __male_person;
    static const lorem::female_person_ru_RU __female_person;

    return g == lorem::gender::male
        ? static_cast<lorem::person::impl const *>(& __male_person)
        : static_cast<lorem::person::impl const *>(& __female_person);
}
