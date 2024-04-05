#define _USE_MATH_DEFINES  // для "пи"
#include <windows.h>
#include <glut.h>
#include <cmath>   // для мат. функций

LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);

GLfloat FAngle;

int main()
{
	//Получаем хендл приложения, потребуется при создании класса окна и самого окна.
	HINSTANCE histance = GetModuleHandleW(NULL);

	//Создаем класс окна.
	WNDCLASSEX wclass = { 0 };          //Обнуляем структуру с самого начала, так как заполнять будем не все поля.
	wclass.cbSize = sizeof(WNDCLASSEX);      //По размеру структуры Windows определит, какая версия API была использована.
	wclass.style = CS_HREDRAW | CS_VREDRAW;    //Говорим окну перерисовываться при изменении размеров окна.
	wclass.lpfnWndProc = WndProc;        //Указываем функцию обработки сообщений.
	wclass.hInstance = histance;        //Указываем хендл приложения.
	wclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);    //GetStockObject возвращает хендл на белую кисточку, для фона окна
	wclass.lpszClassName = L"MYCLASS";      //Имя данного класса, должно быть уникальным, иначе, если класс с таким именем уже зарегестрирован, то в регистрации будет отказано.
	//Регистрируем класс окна.
	RegisterClassEx(&wclass);

	HWND w;

	//Создаем окно.
	w = CreateWindowExW(
		0,
		L"MYCLASS",                //Имя класса.
		L"Title",                //Заголовок окна.
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, //WS_OVERLAPPEDWINDOW,          //Тип окна, влияет на отображение системного меню, кнопок в верхнем правом углу и т.п.
		50, 50,                  //Координаты окна.
		500, 500,                //Ширина окна.
		0,                    //Ссылка на родительское окно.
		0,                    //Хендл меню.
		histance,                //Хендл приложения, получаем его функцией GetModuleHandleW.
		0
	);



	//Показываем окно, если этого не сделать окно не будет отображено.
	ShowWindow(w, SW_SHOW);
	//Обновляем окно.
	UpdateWindow(w);


	//Запускаем цикл обработки сообщений окна.
	MSG msg = { 0 };
	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);  //Преобразуем виртуальную клавишу в ASCII-код и посылаем сообщение WM_CHAR (тут не нужно.Необходимо, если надо работать с текстом, вводимым с клавиатуры)
		DispatchMessage(&msg);  //Передаем сообщения для обработки в "главную функцию обработки сообщений"
	}
	return 0;
}

void Axes(GLfloat cx, GLfloat cy, GLfloat cz, GLfloat size)
{
	size = size / 2.0;
	glBegin(GL_LINES);
	// ось x
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(cx - size, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(cx + size, 0.0, 0.0);
	// ось y
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, cy - size, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, cy + size, 0.0);
	// ось z
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, cz - size);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, cz + size);
	glEnd();
}

void Cube(GLfloat cx, GLfloat cy, GLfloat cz, GLfloat size, byte rf, byte gf, byte bf, byte rt, byte gt, byte bt)
{
	byte rm, gm, bm;
	// вычислим промежуточный цвет
	rm = rf + (rt - rf) / 2;
	gm = gf + (gt - gf) / 2;
	bm = bf + (bt - bf) / 2;
	// рисуем грани куба
	size = size / 2.0;
	glBegin(GL_QUADS);
	// нижняя грань
	glColor3ub(rf, gf, bf);
	glVertex3f(cx + size, cy - size, cz - size);
	glColor3ub(rm, gm, bm);
	glVertex3f(cx + size, cy - size, cz + size);
	glColor3ub(rt, gt, bt);
	glVertex3f(cx - size, cy - size, cz + size);
	glColor3ub(rm, gm, bm);
	glVertex3f(cx - size, cy - size, cz - size);
	// задняя грань
	glColor3ub(rf, gf, bf);
	glVertex3f(cx - size, cy - size, cz - size);
	glColor3ub(rm, gm, bm);
	glVertex3f(cx - size, cy + size, cz - size);
	glColor3ub(rt, gt, bt);
	glVertex3f(cx + size, cy + size, cz - size);
	glColor3ub(rm, gm, bm);
	glVertex3f(cx + size, cy - size, cz - size);
	// левая грань
	glColor3ub(rt, gt, bt);
	glVertex3f(cx - size, cy - size, cz + size);
	glColor3ub(rm, gm, bm);
	glVertex3f(cx - size, cy + size, cz + size);
	glColor3ub(rf, gf, bf);
	glVertex3f(cx - size, cy + size, cz - size);
	glColor3ub(rm, gm, bm);
	glVertex3f(cx - size, cy - size, cz - size);
	// передняя грань
	glColor3ub(rm, gm, bm);
	glVertex3f(cx + size, cy - size, cz + size);
	glColor3ub(rf, gf, bf);
	glVertex3f(cx + size, cy + size, cz + size);
	glColor3ub(rm, gm, bm);
	glVertex3f(cx - size, cy + size, cz + size);
	glColor3ub(rt, gt, bt);
	glVertex3f(cx - size, cy - size, cz + size);
	// правая грань
	glColor3ub(rm, gm, bm);
	glVertex3f(cx + size, cy - size, cz - size);
	glColor3ub(rt, gt, bt);
	glVertex3f(cx + size, cy + size, cz - size);
	glColor3ub(rm, gm, bm);
	glVertex3f(cx + size, cy + size, cz + size);
	glColor3ub(rf, gf, bf);
	glVertex3f(cx + size, cy - size, cz + size);
	// верхняя грань
	glColor3ub(rm, gm, bm);
	glVertex3f(cx - size, cy + size, cz - size);
	glColor3ub(rf, gf, bf);
	glVertex3f(cx - size, cy + size, cz + size);
	glColor3ub(rm, gm, bm);
	glVertex3f(cx + size, cy + size, cz + size);
	glColor3ub(rt, gt, bt);
	glVertex3f(cx + size, cy + size, cz - size);
	glEnd();
}

void Diag(GLfloat cx, GLfloat cy, GLfloat cz, GLfloat size)
{
	size = size / 2.0;
	glBegin(GL_LINES);
	// первая пара диагоналей
	glVertex3f(cx - size, cy - size, cz - size);
	glVertex3f(cx + size, cy + size, cz - size);
	glVertex3f(cx - size, cy + size, cz - size);
	glVertex3f(cx + size, cy - size, cz - size);
	// вторая пара диагоналей    
	glVertex3f(cx - size, cy - size, cz + size);
	glVertex3f(cx + size, cy + size, cz + size);
	glVertex3f(cx - size, cy + size, cz + size);
	glVertex3f(cx + size, cy - size, cz + size);
	glEnd();
}

// главная функция обработки сообщений
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_DESTROY:// если этого не сделать, то все ваши жалкие попытки закрыть окно будут проигнорированы
		wglMakeCurrent(0, 0);
		wglDeleteContext(wglGetCurrentContext());
		ReleaseDC(hWnd, wglGetCurrentDC());
		PostQuitMessage(0);// отправляет приложению сообщение WM_QUIT. Принимает код ошибки, который заносится в wParam сообщения WM_QUIT
		break;


	case WM_CREATE:
		HGLRC RC;
		HDC   DC;
		PIXELFORMATDESCRIPTOR pfd, * ppfd;

		wglMakeCurrent(0, 0);
		int pixelformat;
		ppfd = &pfd;
		ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
		ppfd->nVersion = 1;
		ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		ppfd->dwLayerMask = PFD_MAIN_PLANE;
		ppfd->iPixelType = PFD_TYPE_RGBA;
		ppfd->cColorBits = 16;
		ppfd->cDepthBits = 16;
		ppfd->cAccumBits = 0;
		ppfd->cStencilBits = 0;

		DC = GetDC(hWnd);	 	//1

		pixelformat = ChoosePixelFormat(DC, ppfd); //2
		SetPixelFormat(DC, pixelformat, ppfd);				//3
		RC = wglCreateContext(DC); //4
		wglMakeCurrent(DC, RC); 	//5

		SetTimer(hWnd,             // хэндл главного окна
			0,            // идентификатор таймера
			100,                 // интервал - 0.10 секунды
			NULL);     // процедуры таймера нет

		break;

	case WM_TIMER:
		FAngle = FAngle + 1.0;
		if (FAngle > 359.0) FAngle = 0.0;
		
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_SIZE:
		WORD w, h;
		w = LOWORD(lParam);
		h = HIWORD(lParam);
		glViewport(0, 0, w, h);
		break;

	case WM_PAINT:
		// очищаем буфер кадра, устанавливая цвет его пикселей
		// равным цвету очистки
		glClearColor(0.0, 0.0, 0.25, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);
		// будем рисовать полигоны линиями
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// задаем видовое преобразование
		glLoadIdentity();
		glRotatef(-20.0, 1.0, 0.0, 0.0);
		glRotatef(20.0, 0.0, 1.0, 0.0);
		//рисуем оси координат
		Axes(0.0, 0.0, 0.0, 1.7);
		//рисуем зеленый куб c центром в начале координат и стороной 0.25
		// не применяя никакого преобразования моделирования
		glPushMatrix();
		glRotatef(FAngle, 0.0, 0.0, 1.0);
		Cube(0.0, 0.0, 0.0, 0.25, 0, 255, 0, 0, 128, 0); // clLime, clGreen
		Diag(0.0, 0.0, 0.0, 0.25);
		glPopMatrix();
		//рисуем красный куб c центром точке (-0.5, 0.0, 0.0) и стороной 0.25
		//преобразование моделирования перенос и поворот относительно оси x
		glPushMatrix();
		glTranslatef(-0.5, 0.0, 0.0);
		glRotatef(-FAngle, 1.0, 0.0, 0.0);
		Cube(0.0, 0.0, 0.0, 0.25, 255, 0, 0, 255, 255, 0); // clRed, clYellow
		//мы умеем рисовать диагонали только в плоскости, параллельной xOy
		//повернем его на 90 градусов относительно y,
		   //чтобы он оказался в плоскости yOz
		glRotatef(-90.0, 0.0, 1.0, 0.0);
		Diag(0.0, 0.0, 0.0, 0.25);
		glPopMatrix();
		//рисуем красный куб c центром точке (0.5, 0.0, 0.0) и стороной 0.25
		   //преобразование моделирования – перенос и поворот относительно оси x
		glPushMatrix();
		glTranslatef(0.5, 0.0, 0.0);
		glRotatef(FAngle, 1.0, 0.0, 0.0);
		Cube(0.0, 0.0, 0.0, 0.25, 255, 0, 0, 255, 255, 0); //clRed, clYellow
		glRotatef(90.0, 0.0, 1.0, 0.0);
		Diag(0.0, 0.0, 0.0, 0.25);
		glPopMatrix();
		// рисуем синий куб c центром точке (0.0, -0.5, 0.0) и стороной 0.25
		// преобразование моделирования – перенос и поворот относительно оси y
		glPushMatrix();
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(-FAngle, 0.0, 1.0, 0.0);
		Cube(0.0, 0.0, 0.0, 0.25, 0, 255, 255, 0, 0, 255); // clAqua, clBlue
		glRotatef(-90.0, 1.0, 0.0, 0.0);
		Diag(0.0, 0.0, 0.0, 0.25);
		glPopMatrix();
		// рисуем синий куб c центром точке (0.0, 0.5, 0.0) и стороной 0.25
		   // преобразование моделирования – перенос и поворот относительно оси y
		glPushMatrix();
		glTranslatef(0.0, 0.5, 0.0);
		glRotatef(FAngle, 0.0, 1.0, 0.0);
		Cube(0.0, 0.0, 0.0, 0.25, 0, 255, 255, 0, 0, 255); //clAqua, clBlue
		glRotatef(90.0, 1.0, 0.0, 0.0);
		Diag(0.0, 0.0, 0.0, 0.25);
		glPopMatrix();
		// после завершения рисования необходимо выполнить обмен буферов
		// для показа изображения пользователю
		SwapBuffers(wglGetCurrentDC());

		break;

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);//обрабатываем все остальные сообщения обработчиком "по умолчанию"
}