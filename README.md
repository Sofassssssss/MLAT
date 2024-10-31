В формуле есть несколько мелких ошибок и недочетов, которые можно исправить, чтобы она стала более точной и понятной. Вот отредактированный текст:

---

## Описание модели
Пусть самолет имеет координаты \((x, y, z)\), а \(i\)-я вышка имеет координаты \((x_i, y_i, z_i)\). Пусть всего задано \(n > 3\) вышек, тогда существует 

$$
  C_n^2 = \frac{n(n-1)}{2} 
$$

способов выбрать любые две из них. Обозначим расстояние от самолета до \(i\)-й вышки как \(d_i\), а расстояние до \(j\)-й вышки как \(d_j\). Эти расстояния выражаются по формулам

$$
d_i = \sqrt{(x - x_i)^2 + (y - y_i)^2 + (z - z_i)^2},
$$

$$
d_j = \sqrt{(x - x_j)^2 + (y - y_j)^2 + (z - z_j)^2}.
$$

Определим функцию \(d_{ij}(x, y, z)\) как разность расстояний между самолетом и вышками \(i\) и \(j\):

$$
d_{ij}(x, y, z) = |d_i - d_j| = \left| \sqrt{(x - x_i)^2 + (y - y_i)^2 + (z - z_i)^2} - \sqrt{(x - x_j)^2 + (y - y_j)^2 + (z - z_j)^2} \right|.
$$

С другой стороны, мы можем записать, что

$$
d_i = c t_i,
$$

где \(t_i\) — время, за которое сигнал доходит от самолета до \(i\)-й вышки. Тогда обозначим 

$$
d_{ij} = c |t_i - t_j| = c \Delta t_{ij},
$$

где \(c\) — скорость распространения сигнала (в нашем случае, скорость света), а \(\Delta t_{ij}\) — разница времен прибытия сигнала (Time Difference of Arrival, TDOA). Эта информация известна, так как измеряется на вышках.

Для определения координат самолета используем метод наименьших квадратов (МНК):

![telegram-cloud-photo-size-1-5267368898955699407-y](https://github.com/user-attachments/assets/547b6460-db20-41ce-9bca-9b9ab1bde1fa)


Далее будем искать такие решения, которые минимизируют эту сумму, применяя алгоритм Гаусса-Ньютона. Обозначив за \(x\) вектор решений \((x, y, z)\), получим:

$$
x^{(k+1)} = x^{(k)} - (J_f^T J_f)^{-1} J_f^T f(x^{(k)}),
$$

где \(J_f\) — матрица Якоби для системы \(f\). Произведение матриц в вычитаемом является псевдообратной матрицей к \(J_f\), которую можно вычислить с помощью QR-разложения.

## Постановка задачи
Реализовать описанную модель с переопределённой системой, решаемой с помощью нелинейного МНК. Сравнить вычисленные координаты самолета с реальными и реализовать корректировку координат.
