% Понятия и их свойства
user(ivan, graduate, no_experience, programming, high_motivation).
user(maria, student, no_experience, marketing, medium_motivation).
user(alexey, specialist, has_experience, analytics, high_motivation).
user(elena, graduate, has_experience, design, low_motivation).
user(dmitry, graduate, has_experience, programming, high_motivation).

% Вакансии и их характеристики
vacancy(programmer, programming, no_experience_required, high_salary).
vacancy(data_analyst, analytics, experience_required, high_salary).
vacancy(designer, design, no_experience_required, medium_salary).
vacancy(marketer, marketing, experience_required, medium_salary).
vacancy(junior_developer, programming, no_experience_required, medium_salary).

% Рекомендации по развитию
recommendation(no_experience, internship).
recommendation(has_experience, qualification_improvement).
recommendation(high_motivation, leadership_courses).
recommendation(low_motivation, work_with_coach).
recommendation(medium_motivation, career_counseling).

% Связи и отношения
related_to(programming, technology).
related_to(marketing, business).
related_to(analytics, data_analysis).
related_to(design, creativity).

% Отношения is_a
is_a(user, entity).
is_a(vacancy, job).
is_a(recommendation, advice).
is_a(education, attribute).
is_a(experience, attribute).
is_a(field, attribute).
is_a(motivation, attribute).
is_a(domain, category).
is_a(required_experience, attribute).
is_a(salary, attribute).
is_a(recommendation_type, category).
is_a(courses, category).

% Отношения has_property
has_property(ivan, education, graduate).
has_property(ivan, experience, no_experience).
has_property(ivan, field, programming).
has_property(ivan, motivation, high_motivation).
has_property(programmer, salary, high_salary).
has_property(programmer, required_experience, no_experience_required).

% Правила для подбора вакансий
suitable_vacancy(User, Vacancy) :-
    user(User, _, Experience, Field, _),
    vacancy(Vacancy, Field, RequiredExperience, _),
    (
        (RequiredExperience = no_experience_required, Experience = no_experience);
        (RequiredExperience = experience_required, Experience = has_experience)
    ).

% Правила для рекомендаций
recommendation_for(User, Recommendation) :-
    user(User, _, Experience, _, Motivation),
    (recommendation(Experience, Recommendation); recommendation(Motivation, Recommendation)).

% Примеры запросов:
% 1. suitable_vacancy(ivan, Vacancy).
% 2. recommendation_for(maria, Recommendation).
% 3. related_to(Field, Domain).
% 4. vacancy(Job, Field, experience_required, Salary).
% 5. user(User, graduate, _, _, high_motivation).