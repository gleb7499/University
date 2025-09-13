# Лабораторная работа №1 — Контейнеризация и Docker (Вариант 14)

## 1. Цель работы
Закрепить навыки контейнеризации приложений с использованием Docker: упаковка Flask-сервиса, настройка healthcheck, graceful shutdown, организация multi-stage сборки, работа с docker compose, использование переменных окружения и метаданных.

## 2. Шаги сборки и запуска

### Предварительно
Требуется установленный **Docker Desktop v4.45.0** (или совместимый движок) на **Windows 11 24H2**.

### Быстрый старт с Make (рекомендуемый способ)
```powershell
# Просмотр всех доступных команд
make help

# Сборка и запуск
make build
make up

# Проверка здоровья приложения
make health

# Просмотр логов
make logs

# Остановка приложения
make stop

# Полная остановка и удаление сервисов
make down
```

### Альтернативно через Docker команды
```powershell
# Сборка образа вручную
docker build -t gleb7499/lab1-v14:latest .

# Запуск через docker compose
docker compose up -d --build

# Просмотр логов приложения
docker compose logs -f app

# Остановка
docker compose down
```

## 3. Пример логов работы
```
2025-09-16 10:15:04,120 | INFO | ==== Application Startup ==== 
2025-09-16 10:15:04,121 | INFO | Student ID: 220018
2025-09-16 10:15:04,121 | INFO | Student Group: АС-63
2025-09-16 10:15:04,121 | INFO | Student Variant: 14
2025-09-16 10:15:04,122 | INFO | ENV STU_ID=220018
2025-09-16 10:15:04,122 | INFO | ENV STU_GROUP=АС-63
2025-09-16 10:15:04,122 | INFO | ENV STU_VARIANT=14
2025-09-16 10:15:04,123 | INFO | ================================================
2025-09-16 10:15:04,123 | INFO | Starting Flask server on 0.0.0.0:8062
# Запрос на /healthz
2025-09-16 10:15:10,500 | INFO | 200 GET /healthz
# Завершение (docker stop / SIGTERM)
2025-09-16 10:15:20,010 | WARNING | Received signal 15 - initiating graceful shutdown...
2025-09-16 10:15:20,311 | INFO | Stop accepting new connections. Shutdown flag set.
2025-09-16 10:15:20,512 | INFO | Graceful shutdown complete.
```

## 4. Пример запроса к `/healthz`
```powershell
# С помощью Make (рекомендуемый способ)
make health

# Или вручную через PowerShell
Invoke-RestMethod -Uri http://localhost:8062/healthz -Method GET

# Или с помощью curl
curl http://localhost:8062/healthz
```
Пример ответа:
```json
{
  "status": "ok",
  "timestamp": "2025-09-16T07:15:10.500Z"
}
```

## 5. Структура репозитория
```
.
├── Dockerfile
├── docker-compose.yml
├── requirements.txt
├── .dockerignore
├── Makefile
├── README.md
└── src/
    └── app.py
```

## 6. Описание компонентов
- **Flask приложение** (`src/app.py`): реализует маршруты `/` (информация) и `/healthz` (health check), а также `/echo` (тест POST). Логирует переменные окружения и обрабатывает корректное завершение при SIGTERM/SIGINT.
- **Dockerfile**: multi-stage (builder + final), минимальный Alpine образ, непривилегированный пользователь UID 10001, HEALTHCHECK, LABELS с учебными данными.
- **docker-compose.yml**: сервисы `db` (Postgres 16 Alpine) и `app`, volume `data_v14`, переменные окружения для подключения к БД, labels для приложения.

## 7. Метаданные студента
- ФИО: Логинов Глеб Олегович  
- Группа: АС-63  
- StudentID: 220018  
- Email: as006315@g.bstu.by  
- GitHub username: gleb7499  
- Вариант: 14  
- Дата выполнения: 13.09.2025  
- ОС: Windows 11 24H2  
- Docker Desktop/Engine: v4.45.0  

## 8. Дополнительно
- Образ создаётся через multi-stage: зависимости устанавливаются отдельно и копируются в финальный слой для оптимизации размера (<150MB).
- Используется `HEALTHCHECK`, чтобы оркестратор мог отслеживать состояние контейнера.
- `ENTRYPOINT` в exec-форме обеспечивает доставку сигналов приложению (graceful shutdown).
- Логи пишутся в stdout для интеграции с Docker logging driver.

## 9. Команды для быстрого теста

### С помощью Make
```powershell
# Проверка состояния контейнеров
make ps

# Проверка размера образа
make image-size

# Тест graceful shutdown
make graceful-test

# Открыть shell в контейнере
make shell

# Очистка Docker ресурсов
make clean
```

### Прямые Docker команды
```powershell
# Проверка состояния контейнеров
docker ps

# Просмотр health статуса
docker inspect --format='{{json .State.Health}}' as63-220018-v14-app

# Отправка POST на /echo
curl -X POST http://localhost:8062/echo -H "Content-Type: application/json" -d '{"msg":"hello"}'
```
