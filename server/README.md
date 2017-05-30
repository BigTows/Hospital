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
0     | {"level":0,"messages":{"short":"Success","full":"Send data"},"data":[{"first_name":"Александр","second_name":"Чапчук","middle_name":"Юрьевич","sex":"1","phone":"","date":"1998-07-25","email":""}]}
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