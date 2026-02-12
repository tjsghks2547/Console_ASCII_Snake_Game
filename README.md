# Console_ASCII_Snake_Game (프로젝트 의도)
게임 엔진의 전체 흐름을 처음부터 끝까지 다시 정리해보고자 작업하였습니다.



### 개발 기간
- 2026 02.06 ~ 2026. 02.09 (4일) 



### 📖기술 스택 및 개발 환경
- C++



### 💻구현 엔진 기능 및 컨텐츠
<img width="635" height="726" alt="image" src="https://github.com/user-attachments/assets/5f012f23-96d6-4109-af11-bc901e34ebbe" />


- GameInstance를 중심으로 전체 라이플 사이클(Update -> Render -> Free) 흐름을 구성하였습니다.
  
  Update 단계에서 Input, Level, Object , Collision, Event Manager를 분리하여 각 시스템의 역할을 명확히 나누었습니다.

  Renderer 단계에서는 화면에 출력될 객체들의 우선순위를 정렬하여 올바른 렌더링 순서를 보장하도록 설계하였습니다.

  이후 Double Buffering을 적용하여 화면 깜빡임을 최소화하고, 안정적인 콘솔 렌더링이 이루어지도록 구현했습니다.

![Image](https://github.com/user-attachments/assets/e14cb89e-7421-4130-ab7b-d46a5adc2b7b)
    
