% Факты: Информация о пользователе
user(ivan, graduate, no_experience, programming, high_motivation).
user(maria, student, no_experience, marketing, medium_motivation).
user(alexey, specialist, has_experience, analytics, high_motivation).
user(elena, graduate, has_experience, design, low_motivation).
user(sergey, student, no_experience, programming, medium_motivation).
user(dmitry, graduate, has_experience, programming, high_motivation).
user(olga, specialist, has_experience, marketing, high_motivation).
user(anna, student, no_experience, analytics, low_motivation).
user(vladimir, graduate, no_experience, design, medium_motivation).
user(natalia, specialist, has_experience, programming, high_motivation).

% Факты: Доступные вакансии
vacancy(programmer, programming, no_experience_required, high_salary).
vacancy(data_analyst, analytics, experience_required, high_salary).
vacancy(designer, design, no_experience_required, medium_salary).
vacancy(marketer, marketing, experience_required, medium_salary).
vacancy(junior_developer, programming, no_experience_required, medium_salary).
vacancy(senior_analyst, analytics, experience_required, high_salary).
vacancy(art_director, design, experience_required, high_salary).
vacancy(social_media_manager, marketing, no_experience_required, medium_salary).
vacancy(software_engineer, programming, experience_required, high_salary).
vacancy(marketing_assistant, marketing, no_experience_required, low_salary).

% Факты: Рекомендации по разработке
recommendation(no_experience, internship).
recommendation(has_experience, qualification_improvement).
recommendation(high_motivation, leadership_courses).
recommendation(low_motivation, work_with_coach).
recommendation(medium_motivation, career_counseling).
recommendation(no_experience, online_courses).
recommendation(has_experience, advanced_training).
recommendation(high_motivation, project_management).
recommendation(low_motivation, motivational_training).
recommendation(medium_motivation, mentoring_program).

% Правила: Выбор работы
suitable_vacancy(User, Vacancy) :-
    user(User, _, Experience, Field, _),
    vacancy(Vacancy, Field, RequiredExperience, _),
    (
        (RequiredExperience = no_experience_required, Experience = no_experience);   % Без опыта
        (RequiredExperience = experience_required, Experience = has_experience);     % С опытом
        (Experience = has_experience, RequiredExperience \= experience_required)     % Пользователь с опытом может претендовать на вакансии без опыта
    ).


% Правила: Рекомендации по разработке
recommendation_for(User, Recommendation) :-
    user(User, _, Experience, _, Motivation),
    (recommendation(Experience, Recommendation); recommendation(Motivation, Recommendation)).
