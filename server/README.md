# Каталог с Серверной частью


## API
Пример URL для методов
> http://сайт.ru/request/%method%/
### Метод auth (POST)
 Параметры | Значения
----------------|----------------------
name     | Логин пользователя (Полис или Логин врача)
password     | Пароль пользователя
type_user | Тип пользователя, варианты: 1 (Пациент) или 2 (Доктор) по умолчанию пациент

#### Примеры возврата
 Код | JSON - config
----------------|----------------------
0     | {"level":0,"messages":{"short":"Success","full":"You is auth"},"data":{"token":"umeose37j8lodm8uvrvrqjl192"}}
2 | {"level":2,"messages":{"short":"Bad input data","full":""},"data":[]}

### Метод getProfile (POST)
 Параметры | Значения
----------------|----------------------
token     | Token - полученый после авторизации (auth метод)
type_user     | Тип пользователя, варианты: 1 (Пациент) или 2 (Доктор) по умолчанию пациент

#### Примеры возврата
 Код | JSON - config
----------------|----------------------
0     | {"level":0,"messages":{"short":"Success","full":"Send data"},"data":{"first_name":"Александр","second_name":"Чапчук","middle_name":"Юрьевич","sex":"1","phone":"","date":"1998-07-25","email":""}}
2 | {"level":2,"messages":{"short":"You are not authorized","full":"Please use method %auth%"},"data":[]}


### Метод getRecords (POST)
 Параметры | Значения
----------------|----------------------
token     | Token - полученый после авторизации (auth метод)
period | Если true, то возвращает с той даты которая была указана
date     | Дата с которой нужно получить записи по умолчанию NOW()

#### Примеры возврата
 Код | JSON - config
----------------|----------------------
0     | {"level":0,"messages":{"short":"Success","full":"You is auth"},"data":[{"id_record":"1","date":"2017-06-13 18:08:02","id_user":"1234123412341234","first_name":"Александр","id_doctor":"1","second_name":"Чапчук","middle_name":"Юрьевич","sex":"1"}]}
2 | {"level":2,"messages":{"short":"Bad input data","full":""},"data":[]}

### Метод addHistory (POST)
 Параметры | Значения
----------------|----------------------
token     | Token - полученый после авторизации (auth метод)
id_user  | Полис пользователя
text     | Описание

#### Примеры возврата
 Код | JSON - config
----------------|----------------------
0     | {"level":0,"messages":{"short":"Success","full":"You is auth"},"data":[{"id_record":"1","date":"2017-06-13 18:08:02","id_user":"1234123412341234","first_name":"Александр","id_doctor":"1","second_name":"Чапчук","middle_name":"Юрьевич","sex":"1"}]}
2 | {"level":2,"messages":{"short":"Bad input data","full":""},"data":[]}


### Метод getUser (POST)
 Параметры | Значения
----------------|----------------------
token     | Token - полученый после авторизации (auth метод) Токен только врача
id_user  | Полис пользователя

#### Примеры возврата
 Код | JSON - config
----------------|----------------------
0     | {"level":0,"messages":{"short":"Success","full":"Send data"},"data":{"polis":"1234123412341234","first_name":"Александр","second_name":"Чапчук","middle_name":"Юрьевич","sex":"1","phone":"79060780162","date":"1998-07-25","email":"gasfull@mail.ru","photo":"https:\/\/pp.userapi.com\/c620126\/v620126184\/15af5\/a171MPR6ArM.jpg"}}
2 | {"level":2,"messages":{"short":"You are not authorized","full":"Please use method %auth%"},"data":[]}


### Метод getHistory (POST)
 Параметры | Значения
----------------|----------------------
token     | Token - полученый после авторизации (auth метод) Токен только врача
id_user  | Полис пользователя
count | Кол-во записей, по умолчанию 5

#### Примеры возврата
 Код | JSON - config
----------------|----------------------
0     | {"level":0,"messages":{"short":"Success","full":"Send data"},"data":[{"id_history":"1","id_user":"1234123412341234","id_doctor":"1","text":"Ты болен","date":"2017-06-01 14:13:39"},{"id_history":"2","id_user":"1234123412341234","id_doctor":"1","text":"Тест","date":"2017-06-07 12:34:18"},{"id_history":"3","id_user":"1234123412341234","id_doctor":"1","text":"Тест2","date":"2017-06-07 12:34:28"},{"id_history":"4","id_user":"1234123412341234","id_doctor":"1","text":"l55uf4606drr4h288mi512d1q1","date":"2017-06-14 21:45:47"},{"id_history":"5","id_user":"1234123412341234","id_doctor":"1","text":"l55uf4606drr4h288mi512d1q1","date":"2017-06-14 21:48:02"}]}
2 | {"level":2,"messages":{"short":"You are not authorized","full":"Please use method %auth%"},"data":[]}



## Структура Базы данных

```sql

--
-- База данных: `Hospital`
--

-- --------------------------------------------------------

--
-- Структура таблицы `doctor`
--

CREATE TABLE `doctor` (
  `id_doctor` int(11) NOT NULL,
  `first_name` varchar(120) NOT NULL,
  `second_name` varchar(120) NOT NULL,
  `middle_name` varchar(120) NOT NULL,
  `sex` tinyint(1) NOT NULL,
  `password` varchar(1024) NOT NULL,
  `foto` varchar(1024) NOT NULL,
  `date` date NOT NULL,
  `phone` varchar(20) NOT NULL,
  `email` varchar(512) NOT NULL,
  `id_post` int(11) NOT NULL,
  `start_time` time NOT NULL,
  `end_time` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Структура таблицы `history_user`
--

CREATE TABLE `history_user` (
  `id_history` int(11) NOT NULL,
  `id_user` varchar(16) NOT NULL,
  `id_doctor` int(11) NOT NULL,
  `text` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Структура таблицы `post`
--

CREATE TABLE `post` (
  `id_post` int(11) NOT NULL,
  `name` varchar(120) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Структура таблицы `record`
--

CREATE TABLE `record` (
  `id_record` int(11) NOT NULL,
  `id_user` varchar(16) NOT NULL,
  `id_doctor` int(11) NOT NULL,
  `date` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Структура таблицы `user`
--

CREATE TABLE `user` (
  `id_user` varchar(16) NOT NULL,
  `first_name` varchar(120) NOT NULL,
  `second_name` varchar(120) NOT NULL,
  `middle_name` varchar(120) NOT NULL,
  `foto` text NOT NULL,
  `date` date NOT NULL,
  `sex` tinyint(1) NOT NULL,
  `phone` varchar(20) NOT NULL,
  `password` varchar(1024) NOT NULL,
  `email` varchar(512) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `doctor`
--
ALTER TABLE `doctor`
  ADD PRIMARY KEY (`id_doctor`),
  ADD KEY `id_post` (`id_post`);

--
-- Индексы таблицы `history_user`
--
ALTER TABLE `history_user`
  ADD PRIMARY KEY (`id_history`),
  ADD KEY `id_user` (`id_user`),
  ADD KEY `id_doctor` (`id_doctor`);

--
-- Индексы таблицы `post`
--
ALTER TABLE `post`
  ADD PRIMARY KEY (`id_post`);

--
-- Индексы таблицы `record`
--
ALTER TABLE `record`
  ADD PRIMARY KEY (`id_record`),
  ADD KEY `id_doctor` (`id_doctor`),
  ADD KEY `id_user` (`id_user`);

--
-- Индексы таблицы `user`
--
ALTER TABLE `user`
  ADD PRIMARY KEY (`id_user`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `doctor`
--
ALTER TABLE `doctor`
  MODIFY `id_doctor` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `history_user`
--
ALTER TABLE `history_user`
  MODIFY `id_history` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `post`
--
ALTER TABLE `post`
  MODIFY `id_post` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT для таблицы `record`
--
ALTER TABLE `record`
  MODIFY `id_record` int(11) NOT NULL AUTO_INCREMENT;
--
-- Ограничения внешнего ключа сохраненных таблиц
--

--
-- Ограничения внешнего ключа таблицы `doctor`
--
ALTER TABLE `doctor`
  ADD CONSTRAINT `doctor_ibfk_1` FOREIGN KEY (`id_post`) REFERENCES `post` (`id_post`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Ограничения внешнего ключа таблицы `history_user`
--
ALTER TABLE `history_user`
  ADD CONSTRAINT `history_user_ibfk_1` FOREIGN KEY (`id_user`) REFERENCES `user` (`id_user`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `history_user_ibfk_2` FOREIGN KEY (`id_doctor`) REFERENCES `doctor` (`id_doctor`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Ограничения внешнего ключа таблицы `record`
--
ALTER TABLE `record`
  ADD CONSTRAINT `record_ibfk_1` FOREIGN KEY (`id_doctor`) REFERENCES `doctor` (`id_doctor`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `record_ibfk_2` FOREIGN KEY (`id_user`) REFERENCES `user` (`id_user`) ON DELETE CASCADE ON UPDATE CASCADE;

```