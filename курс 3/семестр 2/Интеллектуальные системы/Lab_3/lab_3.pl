% ====== Основные классы ======
class(entity).
class(professional).
class(user, [entity, professional]).  % <-- Множественное наследование
class(vacancy, entity).
class(recommendation, entity).

% ====== Подклассы для recommendation ======
class(education, user).
class(experience, user).
class(motivation, user).
class(field, recommendation).
class(experience, recommendation).
class(motivation, recommendation).
class(education, recommendation).
class(salary, vacancy).
class(required_experience, vacancy).
class(education, vacancy).

% ====== Атрибуты и значения ======
has_attribute(user, name).
has_attribute(user, education).
has_attribute(user, experience).
has_attribute(user, field).
has_attribute(user, motivation).

has_attribute(vacancy, field).
has_attribute(vacancy, required_experience).
has_attribute(vacancy, salary).

has_attribute(recommendation, type).
has_attribute(recommendation, description).

% ====== Значения атрибутов пользователей ======
has_value(ivan, name, ivan).
has_value(ivan, education, graduate).
has_value(ivan, experience, no_experience).
has_value(ivan, field, programming).
has_value(ivan, motivation, high_motivation).

has_value(maria, name, maria).
has_value(maria, education, student).
has_value(maria, experience, no_experience).
has_value(maria, field, marketing).
has_value(maria, motivation, medium_motivation).

has_value(alexey, name, alexey).
has_value(alexey, education, specialist).
has_value(alexey, experience, has_experience).
has_value(alexey, field, analytics).
has_value(alexey, motivation, high_motivation).

% ====== Значения атрибутов вакансий ======
has_value(programmer, field, programming).
has_value(programmer, required_experience, no_experience_required).
has_value(programmer, salary, high_salary).

has_value(data_analyst, field, analytics).
has_value(data_analyst, required_experience, experience_required).
has_value(data_analyst, salary, high_salary).

has_value(designer, field, design).
has_value(designer, required_experience, no_experience_required).
has_value(designer, salary, medium_salary).

% ====== Значения атрибутов рекомендаций ======
has_value(internship, type, education).
has_value(internship, description, 'Gain experience through internships').

has_value(qualification_improvement, type, experience).
has_value(qualification_improvement, description, 'Improve professional qualifications').

has_value(leadership_courses, type, motivation).
has_value(leadership_courses, description, 'Develop leadership skills').

has_value(work_with_coach, type, motivation).
has_value(work_with_coach, description, 'Increase motivation with a coach').

has_value(career_counseling, type, motivation).
has_value(career_counseling, description, 'Get career counseling').

% ====== Демонстративная процедура ======
show_user_info(User) :-
    has_value(User, name, Name),
    has_value(User, education, Education),
    has_value(User, experience, Experience),
    has_value(User, field, Field),
    has_value(User, motivation, Motivation),
    format('User: ~w~nEducation: ~w~nExperience: ~w~nField: ~w~nMotivation: ~w~n',
           [Name, Education, Experience, Field, Motivation]).

% ====== Диагностическая процедура ======
suitable_vacancy(User, Vacancy) :-
    has_value(User, field, Field),
    has_value(User, experience, Experience),
    has_value(Vacancy, field, Field),
    has_value(Vacancy, required_experience, RequiredExperience),
    (
        (RequiredExperience = no_experience_required, Experience = no_experience);
        (RequiredExperience = experience_required, Experience = has_experience)
    ).

diagnose_vacancy(User) :-
    suitable_vacancy(User, Vacancy),
    format('Recommended vacancy for ~w is ~w.~n', [User, Vacancy]).

% ====== Рекомендательная процедура ======
recommendation_for(User, Recommendation) :-
    has_value(User, experience, Experience),
    has_value(User, motivation, Motivation),
    (
        (Experience = no_experience, Recommendation = internship);
        (Experience = has_experience, Recommendation = qualification_improvement);
        (Motivation = high_motivation, Recommendation = leadership_courses);
        (Motivation = medium_motivation, Recommendation = career_counseling);
        (Motivation = low_motivation, Recommendation = work_with_coach)
    ).

recommend_to_user(User) :-
    recommendation_for(User, Recommendation),
    has_value(Recommendation, description, Description),
    format('Recommendation for ~w: ~w~n', [User, Description]).
