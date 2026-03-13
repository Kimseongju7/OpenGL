# OpenGL 입문 설명서

## 1. OpenGL이란?

**OpenGL(Open Graphics Library)** 은 2D/3D 그래픽을 화면에 그리기 위한 표준 규격입니다.

쉽게 말하면:
- "삼각형을 빨간색으로 (0, 0) 위치에 그려라" 같은 명령을 GPU에게 전달하는 언어
- Windows, macOS, Linux 어디서든 같은 코드로 동작하는 **크로스플랫폼** 그래픽 API
- 게임 엔진, CAD, 시뮬레이션 등의 기반 기술

```
내 코드 → OpenGL 함수 호출 → GPU 드라이버 → 화면에 출력
```

---

## 2. OpenGL 관련 라이브러리

### GL (OpenGL 본체)
- **역할**: 실제 그래픽 명령어 집합. 점, 선, 삼각형을 그리고 색상, 변환, 조명 등을 처리
- **함수 예시**: `glBegin()`, `glVertex3f()`, `glColor3f()`, `glClear()`
- **헤더**: `#include <OpenGL/gl.h>` (macOS) / `#include <GL/gl.h>` (Windows)

### GLU (GL Utility Library)
- **역할**: OpenGL을 편하게 쓸 수 있는 유틸리티 함수 모음. 카메라 설정, 구/원통 등 기본 도형 생성
- **함수 예시**: `gluLookAt()` (카메라 위치 설정), `gluPerspective()` (원근감), `gluSphere()` (구 그리기)
- **헤더**: `#include <OpenGL/glu.h>` (macOS) / `#include <GL/glu.h>` (Windows)
- macOS에서는 `#include <GLUT/glut.h>` 하나만 써도 자동으로 포함됨

### GLUT / freeGLUT (GL Utility Toolkit)
- **역할**: 창 생성, 키보드/마우스 입력, 이벤트 루프 등 OS와의 인터페이스를 담당
  - OpenGL 자체는 "창을 만드는 방법"을 모름. GLUT이 그 역할을 함
- **함수 예시**: `glutCreateWindow()`, `glutDisplayFunc()`, `glutMainLoop()`
- **헤더**: `#include <GLUT/glut.h>` (macOS) / `#include <glut.h>` (Windows, 수업 기준)
- macOS에는 GLUT.framework이 내장되어 있음
- Windows에서는 `glut32.dll` 파일이 필요

### glaux (GL Auxiliary Library) — 구식
- **역할**: BMP 이미지 로드 등 보조 기능. 현재는 거의 사용 안 함
- Windows 전용이며 macOS에는 존재하지 않음
- 수업 자료가 예전 Windows 환경 기준이라 목록에 있을 뿐, 실제 수업에서 거의 안 씀

---

## 3. 설정 파일별 역할

### `main.c` — 메인 소스 코드
```c
#ifdef __APPLE__
#include <GLUT/glut.h>   // macOS
#else
#include <glut.h>        // Windows (수업 기준)
#endif
```
- `#ifdef __APPLE__` : 운영체제에 따라 다른 헤더를 포함하는 전처리기 조건문
- macOS와 Windows에서 같은 코드가 동작하도록 처리

---

### `Makefile` — macOS 빌드 스크립트
```makefile
CC = gcc
CFLAGS = -Wall -Wno-deprecated
LDFLAGS = -framework OpenGL -framework GLUT -framework Cocoa
```
- `CC`: 사용할 컴파일러 (gcc)
- `CFLAGS`: 컴파일 옵션
  - `-Wall`: 모든 경고 표시
  - `-Wno-deprecated`: deprecated 경고 숨김 (macOS에서 OpenGL이 deprecated 처리되어 있어서)
- `LDFLAGS`: 링크 옵션 (어떤 라이브러리를 연결할지)
  - `-framework OpenGL`: OpenGL + GLU 포함
  - `-framework GLUT`: GLUT 포함
  - `-framework Cocoa`: macOS 창 시스템
- **사용법**: `make` (빌드), `make run` (빌드+실행), `make clean` (정리)

---

### `CMakeLists.txt` — 크로스플랫폼 빌드 설정
```cmake
cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)
...
if(WIN32)
    # Windows 설정
elseif(APPLE)
    # macOS 설정
endif()
```
- CMake가 읽는 설정 파일
- Windows/macOS를 자동으로 감지해서 각각에 맞는 빌드 명령을 생성
- 교수님(Windows)이 이 파일로 빌드하면 자동으로 Windows용으로 컴파일됨

---

### `.vscode/c_cpp_properties.json` — IntelliSense 설정
- VSCode가 코드를 분석할 때 어디서 헤더 파일을 찾을지 알려주는 파일
- 빨간 줄(오류 표시) 없애고 자동완성 되게 해줌
- **실제 빌드와는 무관** (편집기 표시 용도)

### `.vscode/tasks.json` — 빌드 태스크
- `Cmd+Shift+B` 눌렀을 때 실행되는 빌드 명령 정의
- "Build", "Build & Run", "Clean" 태스크 포함

### `.vscode/launch.json` — 디버그 설정
- F5로 디버깅 시작할 때 사용하는 설정
- 빌드 후 자동으로 디버거 연결

### `.vscode/settings.json` — CMake Tools 설정
- CMake 빌드 결과물을 `build/` 폴더에 저장하도록 지정

---

## 4. CMake란?

### 문제: 플랫폼마다 빌드 방법이 다름
```
macOS:   gcc main.c -framework OpenGL -framework GLUT -o main
Windows: cl main.c opengl32.lib glut32.lib /Fe:main.exe
Linux:   gcc main.c -lGL -lGLU -lglut -o main
```
같은 코드인데 빌드 명령이 완전히 달라서 불편함.

### 해결: CMake
- **CMake는 빌드 시스템 생성기**
- `CMakeLists.txt` 하나만 작성하면, 각 플랫폼에 맞는 빌드 파일을 자동 생성
- macOS → Makefile 생성
- Windows → Visual Studio 프로젝트(.sln) 생성
- Linux → Makefile 생성

```
CMakeLists.txt
      ↓ cmake ..
   빌드 파일 생성 (Makefile / .sln 등)
      ↓ cmake --build .
    실행 파일 완성
```

### 우리 프로젝트에서 CMake 설정 방법
```cmake
find_package(OpenGL REQUIRED)   # OpenGL 라이브러리 자동 탐색
find_package(GLUT REQUIRED)     # GLUT 라이브러리 자동 탐색

if(WIN32)
    target_link_libraries(... GLUT::GLUT)           # Windows
elseif(APPLE)
    target_link_libraries(... GLUT::GLUT "-framework Cocoa")  # macOS
endif()
```
- `find_package()`: CMake가 시스템에서 라이브러리를 자동으로 찾아줌
- `target_link_libraries()`: 찾은 라이브러리를 실행 파일에 연결

---

## 5. 전체 흐름 요약

```
소스 코드 (main.c)
    ↓
CMakeLists.txt 또는 Makefile
    ↓ 빌드
실행 파일 (main / OpenGLProject.exe)
    ↓ 실행
GLUT이 창 생성 → OpenGL이 그래픽 렌더링 → 화면 출력
```
