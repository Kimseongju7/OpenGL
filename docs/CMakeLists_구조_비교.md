# CMakeLists.txt 구조 비교

## 방식 A: 현재 구조 (주차별 디렉토리 + 단일 실행파일)

### 디렉토리 구조
```
OpenGL/
├── CMakeLists.txt
├── week1/
│   ├── CMakeLists.txt
│   ├── example1.cpp
│   └── example_teapot.cpp   ← main()이 두 개 → 컴파일 에러!
└── week2/
    ├── CMakeLists.txt
    └── example1.cpp
```

### CMakeLists.txt 내용
```cmake
file(GLOB SOURCES "*.cpp" "*.c")
add_executable(OpenGLProject ${SOURCES})  # 모든 소스를 하나의 실행파일로 합침
```

### 동작 방식
- 디렉토리 내 모든 `.cpp`를 **하나의 실행파일**로 합침
- 각 `.cpp`에 `main()`이 하나씩 있으면 → **`main` 중복 컴파일 에러 발생**
- 따라서 디렉토리당 소스파일이 **1개**이거나, 하나의 프로그램을 **여러 파일로 분할**할 때만 사용 가능

### 빌드 및 실행 방법
```bash
cd week1
mkdir build && cd build
cmake ..
cmake --build .
./OpenGLProject   # 실행파일 이름이 항상 OpenGLProject로 고정
```

### 장점
- CMakeLists.txt 구조가 단순
- 하나의 프로그램을 여러 `.cpp`로 분할 작성할 때 적합 (header, source 분리 등)

### 단점
- 소스파일이 늘어나면 **주차마다 디렉토리를 새로 만들어야 함**
- 각 예제가 독립 실행파일이어야 하는 수업 환경에는 부적합
- 실행파일 이름이 `OpenGLProject`로 고정되어 어떤 예제인지 구분 어려움

---

## 방식 B: 소스파일별 실행파일 (src/ 단일 디렉토리)

### 디렉토리 구조
```
OpenGL/
├── CMakeLists.txt
├── src/
│   ├── week1_example1.cpp     → 실행파일: week1_example1
│   ├── week1_teapot.cpp       → 실행파일: week1_teapot
│   ├── week2_example1.cpp     → 실행파일: week2_example1
│   └── week3_lighting.cpp     → 실행파일: week3_lighting
└── build/
    ├── week1_example1
    ├── week1_teapot
    └── week2_example1
```

### CMakeLists.txt 내용
```cmake
cmake_minimum_required(VERSION 3.10)
project(OpenGLCourse)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp")

foreach(SOURCE ${SOURCES})
    get_filename_component(TARGET_NAME ${SOURCE} NAME_WE)  # 확장자 제거 (예: week1_example1)
    add_executable(${TARGET_NAME} ${SOURCE})               # 소스 1개 → 실행파일 1개

    find_package(OpenGL REQUIRED)
    target_link_libraries(${TARGET_NAME} OpenGL::GL)

    if(APPLE)
        find_package(GLUT REQUIRED)
        target_link_libraries(${TARGET_NAME} GLUT::GLUT "-framework Cocoa")
        target_compile_options(${TARGET_NAME} PRIVATE -Wno-deprecated)
    elseif(WIN32)
        find_package(GLUT REQUIRED)
        target_link_libraries(${TARGET_NAME} GLUT::GLUT)
    endif()
endforeach()
```

### 동작 방식
- `src/` 안의 `.cpp` 파일을 하나씩 순회
- 파일 이름에서 확장자를 제거한 이름으로 **각각 독립된 실행파일** 생성
- `main()`이 파일마다 있어도 전혀 문제 없음

### 빌드 및 실행 방법
```bash
mkdir build && cd build
cmake ..
cmake --build .

./week1_example1    # 개별 실행
./week1_teapot
./week2_example1
```

### 장점
- 새 예제 추가 시 `src/`에 `.cpp` 파일만 추가하면 됨 (CMakeLists.txt 수정 불필요)
- 실행파일 이름이 소스파일 이름과 동일 → 직관적
- 디렉토리 구조가 단순하고 `build/` 하나로 전체 관리
- 수업처럼 예제가 독립적인 환경에 최적

### 단점
- 파일이 많아지면 `src/` 안이 뒤섞일 수 있음 (파일명 규칙으로 보완 가능)
- 주차별 독립 빌드 불가 (항상 전체 빌드)
- 하나의 프로그램을 여러 `.cpp`로 분할할 경우 별도 처리 필요

---

## 한눈에 비교

| 항목 | 방식 A (현재) | 방식 B (소스별 실행파일) |
|---|---|---|
| 새 예제 추가 | 주차 디렉토리 새로 생성 | `src/`에 파일만 추가 |
| 실행파일 이름 | 항상 `OpenGLProject` | 소스파일 이름과 동일 |
| 디렉토리 수 | 주차마다 증가 | 항상 1개 (`src/`) |
| build 디렉토리 | 주차마다 각각 필요 | 루트에 1개로 통합 |
| main() 중복 | 에러 발생 | 문제 없음 |
| CMakeLists.txt 수정 | 새 주차마다 복사 | 수정 불필요 |
| 수업 예제 환경 적합성 | 낮음 | 높음 |

---

## 결론

수업에서 각 예제가 독립 실행 프로그램인 경우라면 **방식 B**가 적합하다.
파일명을 `week1_example1.cpp`, `week2_lighting.cpp`처럼 통일하면 정렬도 자연스럽게 된다.
