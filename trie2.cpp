#include "trie1.cpp"
TrieNode* r_Aa = getNewNode(); // Префиксное дерево для ПРС
TrieNode *getNewNode(void) {
	struct TrieNode* a =  new TrieNode; // Выделяем память для нового узла
	for (US i = 0; i < rza; ++i) a->deti[i] = nullptr; // Инициализируем указатели на детей значением nullptr
	a->list = false; // Выставляем значение list, указывающее на то что этот узел не является концом какого-либо слова
	return a;
}
void insKey(CUC* a) { // Используются глобальные переменные
/* Логика. На вход функция принимает си-строку unsigned char. Символы А-Я, а-я (включая Ё и ё)), дефис и знак нижнего подчёркивания
в кодировке ASCII+CP866. Слово добавляется в структуру префиксного дерева, если его нет. Если принятый ключ является префиксом в структуре
дерева (или словом), то, соответствующий узел помечается (заново помечается) листовым для этого ключа. Нулевое, слишком длинное (короткое)
или содержащее недопустимые символы слово в дерево не добавляется */
	US b = 0; // Количество символов (без завершающего ноль-символа) в принятой строке
	while (a[b] != 0) { // Оцениваем количество символов в принятой строке
		++b;
		if (b == rzf + 1) return; // Если исходная строка превышает допустимую длину или (возможно) нулевая (0Б)
	}
	if (b < 1 || b < rzg) return; // Если исходная строка слишком короткая
	for (US i = 0; i < b; ++i) if (a[i] < 45 || (a[i] > 45 && a[i] < 95) || (a[i] > 95 && a[i] < 128) || ((a[i] > 175 && a[i] < 224)) || a[i] > 241) return; // Проверка символов слова на валидность
	US c; // Индекс символа принятого слова в структуре префиксного дерева (например, буква "А" имеет индекс ноль)
	TrieNode* d = r_Aa; // Создаём указатель на указатель корневого узла префиксного дерева
	for (US i = 0; i < b; ++i) { // Последовательно, символ за символом, добавляем ключ в префиксное дерево
		if (a[i] > 127 && a[i] < 176) c = a[i] - 128; // Если это буква из диапазона А-Я и а-п
		else if (a[i] > 223 && a[i] < 242) c = a[i] - 176; // Если это буква из диапазона р-я, Ё и ё
		else if (a[i] == 45) c = 66; // Если это дефис
		else c = 67; // Значит это знак нижнего подчёркивания
		if (d->deti[c] == nullptr) d->deti[c] = getNewNode(); // Если такой префикс отсутствует, то создаём новый узел
		d = d->deti[c]; // Перемещаемся далее по структуре дерева
	}
	d->list = 1; // Помечаем последний узел как лист (конец слова)
}
void bldTrie(void) { // Используется глобальные переменные
/* Логика. Побайтно просматривается словарь. Считанное слово конвертируется из UTF-8 в CP866, а затем, добавляется в префиксное дерево */
	UI a = 0; // Счётчик количество байт в ПРС
	char b[rzf * 4 + 1]; // Си-срока для очередного считанного слова из ПРС
	US c = 0; // Счётчик количества байт в считанном слове из ПРС
	while (slv[a] != 0) { // Считываем данные из ПРС (посимвольно)
		if (slv[a] == 32) { // Если пробел
			if (c > 0) { // Если есть считанное слово
				b[c] = 0; // "Зануляем" считанное слово
				convUTF8toCP866(b, rzf); // Конвентируем считанное слово
				insKey(rez); // Добавляем в префиксное дерево считанное слово
				c = 0; // Обнуляем счётчик байт считанного слова
			}
		}
		else {
			b[c] = slv[a]; // Побайтно собираем слово
			++c;
		}
		if (a == rzh * 4 + 2) return; // Если ПРС превышает допустимую длину или (возможно) нулевой (0Б)
		++a;
	}
}
US findWords(CUC* a, US e) { // Используется глобальные переменные
/* Логика. На вход функция принимает си-строку unsigned char. Символы А-Я, а-я (включая Ё и ё)), дефис и знак нижнего подчёркивания
в кодировке ASCII+CP866 и код поиска. Префикс и код поиска проверяются на валидность. При поиске в два захода, алгоритм откидывает
совпадающие слова. Например: "Интернет" и "интернет"; в приведённом примере второй результат поиска удаляется */
	if (e < 1 || e > 3) return 0; // Если значение кода поиска невалидно (можно: 1 - ищем слова (совпадения по префиксу) с большой буквы, 2 - с маленькой буквы и 3 - с большой и маленькой)
	if (rzi == 0) return 0; // Если максимально допустимое количество предлагаемых пользователю слов по введённому префиксу равно нулю
	US b = 0; // Количество символов (без завершающего ноль-символа) в принятой строке
	while (a[b] != 0) { // Оцениваем количество символов в принятой строке
		++b;
		if (b == rzf + 1) return 0; // Если исходная строка превышает допустимую длину или (возможно) нулевая (0Б)
	}
	if (b < rzj) return 0; // Если префикс слишком короткий
	if (e == 2 && (a[0] < 160 || (a[0] > 175 && a[0] < 224) || a[0] == 240 || a[0] > 241)) return 0; // Если надо искать слова начинающиеся с маленькой буквы, но префикс не начинается с маленькой буквы
	if ((a[0] < 128 && a[0] > 159) && a[0] != 240) return 0; // Иначе, если префикс не начинается с прописной буквы
	US c; // Индекс символа принятого слова в структуре префиксного дерева (например, буква "А" имеет индекс ноль)
	TrieNode* d = r_Aa; // Создаём указатель на указатель корневого узла префиксного дерева и заходим в корневой узел структуры
	US g = 0; // Счётчик количества символов в си-строке с вариантами найденных по префиксу слов
	US h = 0; // Регистратор количества найденных слов в первой структуре (при последовательном поиске в двух деревьях)
	US z = 0; // Количество найденных (возвращаемое функцией значение) по префиксу слов
	if (a[0] > 127 && a[0] < 176) c = a[0] - 128; // Если это буква из диапазона А-Я и а-п
	else c = a[0] - 176; // Если это буква из диапазона р-я, Ё и ё
	if (e != 3) e = 1; // Теперь эта переменная определяет количество циклов поиска (один раз)
	else e = 2; // Иначе, в дереве производим поиск два раза (префикс начинается с большой буквы и префикс начинается с маленькой (меняем строчную на прописную) буквы)
	for (US i = 0; i < e; ++i) { // Просматриваем необходимое количество раз (основной цикл)
		if (e == 2) { // Если ищем в два захода
			if (i == 1) { // Если производим поиск в структуре второй раз (преобразуем первый символ префикса из верхнего в нижний регистр)
				d = r_Aa; // Заходим опять в корневой узел структуры
				if (a[0] == 240) c = 65; // Если это буква Ё
				else c = a[0] - 96; // Иначе, если это буква из диапазона А-Я
			}
		}
		if (d->deti[c] == nullptr) { // Если в дереве совпадение по первому символу префикса отсутствует
			if (e == 1 || i == 1) return z; // Если в дереве ищем один раз или второй раз из двух
			else continue; // Иначе, если поиск производится в два захода (и нет совпадения) переходим к поиску ещё раз
		}
		d = d->deti[c]; // Перемещаемся далее по структуре дерева
		US f = 1; // Счётчик цикла внешний
		for (; f < b; ++f) { // Последовательно ищем оставшуюся часть префикса в соответствующем словаре
			if (a[f] > 127 && a[f] < 176) c = a[f] - 128; // Если это буква из диапазона А-Я и а-п
			else if (a[f] > 223 && a[f] < 242) c = a[f] - 176; // Если это буква из диапазона р-я, Ё и ё
			else if (a[f] == 45) c = 66; // Если это дефис
			else if (a[f] == 95) c = 67; // Если это знак нижнего подчёркивания
			else { // Иначе, если символ префикса не из диапазона
				if (e == 1 || i == 1) return z; // Если ищем в структуре один раз или ищем второй раз из двух
				else break; // Иначе, если поиск производится в два захода (и нет совпадения) выходим из цикла
			}
			if (d->deti[c] == nullptr) { // Если в дереве совпадение по очередному символу префикса отсутствует
				if (e == 1 || i == 1) return z; // Если ищем в структуре один раз или ищем второй раз из двух
				else break; // Иначе, если поиск производится в два захода (и нет совпадения) выходим из цикла
			}
			d = d->deti[c]; // Перемещаемся далее по структуре дерева
		}
		if (f < b) continue; // Если был преждевременный выход из цикла переходим к поиску в дереве второй раз
		TrieNode* m = d; // Создаём указатель на указатель последнего символа префикса в структуре дерева (он поможет нам двигаться "назад" по структуре дерева)
		UC n[rzf - rzj]; // Маршрут (маршруты) в структуре префиксного дерева по существующим буквам после префикса
		US o = 0; // Индекс последнего элемента в маршруте
		n[o] = 0; // Выставляем позицию поиска (возможного ребёнка для последнего символа префикса) в ноль
		bool p; // Регистратор дальнейших действий алгоритма: 0 - не смогли продвинуться вперёд или назад (конец алгоритма) и 1 - сделали шаг вперёд или назад
		do { // Собираем (ищем) слова (самая сложная часть алгоритма)
			f = 0; // Теперь это регистратор совпадения слов в структурах
			p = 0; // Пока нет шага вперёд или назад, взводим регистратор действий на завершение алгоритма
			for (US j = n[o]; j < rza; ++j) { // Ищем продолжение префикса
				if (d->deti[j] != nullptr) { // Если есть продолжение
					d = d->deti[j]; // Делаем шаг вперёд по структуре дерева
					if (j < 48) var[g] = j + 128; // Если это буква из диапазона А-Я и а-п
					else if (j > 47 && j < 66) var[g] = j + 176; // Если это буква из диапазона р-я, Ё и ё
					else if (j == 66) var[g] = 45; // Если это дефис
					else var[g] = 95; // Значит это знак нижнего подчёркивания
					++g; // Смещаемся вперёд на символ в результирующей строке с вариантами слов
					n[o] = j; // Фиксируем точку (код буквы) в маршруте
					++o; // Смещаемся вперёд на шаг по маршруту
					n[o] = 0; // Выставляем позицию поиска (возможного ребёнка для текущего узла) с нуля
					if (d->list == 1) { // Если это конец слова
						if (h > 0 && i == 1) { // Если ищем в два захода, в 1-вом что-то нашли и поиск в структуре идёт второй раз
							US r = 0; // Индекс сравниваемого символа в строке с вариантами слов
							US s; // Код символа в CP866 преобразованный из порядкового номера буквы в алфавите
							US t; // Счётчик цикла внешний
							for (US k = 0; k < h; ++k) { // Начинаем сравнение последнего найденного слова с найденными ранее словами в 1-ой просматриваемой структуре на факт совпадения
								for (t = 0; t < o; ++t) { // Посимвольное сравнение последнего найденного слова с очередным словом из 1-ой структуры
									if (var[r] == 32) { // Если в строке с вариантами слов встретили разделяющий (слова) пробел
										++r; // Сдвигаемся на шаг вперёд по строке
										break;
									}
									if (n[t] < 48) s = n[t] + 128; // Если это буква из диапазона А-Я и а-п
									else if (n[t] > 47 && n[t] < 66) s = n[t] + 176; // Если это буква из диапазона р-я, Ё и ё
									else if (n[t] == 66) s = 45; // Если это дефис
									else s = 95; // Значит это знак нижнего подчёркивания
									if (s != var[r]) {
										do {
											++r; // Сдвигаемся на шаг вперёд по строке
										} while (var[r] != 32); // Продолжаем пока не встретим разделяющий пробел
										++r; // Переводим индекс на начало следующего слова
										break;
									}
									++r; // Продолжаем просматривать строку
								}
								if (t == o && var[r] == 32) { // Если нашли совпадение
									while (var[g - 1] != 32) { // Продолжаем (цикл) пока предыдущий элемент строки не является разделителем (пробелом) между словами
										--g; // Смещаемся на шаг назад (затираем совпадающее слово)
									}
									f = 1; // Зарегистрировали факт нахождения совпадения
									break;
								}
							}
						}
						if (f != 1) { // Если совпадения слов в структурах не нашли
							var[g] = 32; // Добавляем пробел после слова
							++g; // Смещаемся вперёд на символ в результирующей строке с вариантами слов
							++z; // Увеличиваем счётчик найденных слов по префиксу
						}
						if (z == rzi) { // Если нашли максимально допустимое количество слов по префиксу
							var[g] = 0; // Зануляем строку с вариантами слов
							return z;
						}
						if (e == 2) { // Если ищем варианты слов по префиксу в два захода
							if (i == 0) h = z; // Если поиск идёт в первый заход, то, запоминаем количество найденных ранее слов в этом заходе (слова начинаются с большой буквы)
						}
						for (US k = 0; k < o; ++k) { // Добавляем это слово (без пробела в конце) ещё раз в строку с вариан. слов, т.к. возможно, что это слово (или его начальные символы) могут являться частью другого слова
							if (n[k] < 48) var[g] = n[k] + 128; // Если это буква из диапазона А-Я и а-п
							else if (n[k] > 47 && n[k] < 66) var[g] = n[k] + 176; // Если это буква из диапазона р-я, Ё и ё
							else if (n[k] == 66) var[g] = 45; // Если это дефис
							else var[g] = 95; // Значит это знак нижнего подчёркивания
							++g; // Смещаемся вперёд на символ в результирующей строке с вариантами слов
						}
					}
					p = 1; // Смогли сделать шаг вперёд
					break;
				}
			}
			if (p == 0) { // Иначе (если шаг вперёд не получился) пробуем сделать шаг назад
				if (o > 0) { // Если ещё можно сделать шаг назад
					d = m; // Выставляем наш указатель на узел, соответствующий последнему символу префикса, т.к. по этой структуре можно двигаться только в одном направлении (от корня)
					--o; // Делаем индекс предпоследней точки маршрута последним
					for (US j = 0; j < o; ++j) d = d->deti[n[j]]; // Делаем шаг назад за счёт перемещения по маршруту от последнего символа префикса до предпоследней точки маршрута
					++n[o]; // Смещаемся дальше по алфавиту в структуре узла префиксного дерева
					p = 1; // Смогли сделать шаг назад
					if (g > 1 && var[g - 1] != 32) --g; // Если в строке более одного символа и последний символ не является разделяющим пробелом, необходимо при шаге назад удалить последний символ
					else if (g == 1) g = 0; // Иначе, если в стоке остался один символ (он первый и не важно какой) то его неоходимо удалить (сделать шаг назад), что равносильно обнулению строки
				}
			}
		} while (p != 0); // Если сделали шаг вперёд или назад, то продолжаем цикл
	}
	var[g] = 0; // Зануляем строку с вариантами слов
	return z;
}