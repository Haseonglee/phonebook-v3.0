# phonebook-v3.0
배열 재할당, 라인 단위의 입력

init_directory -> names와 numbers 배열 생성
process_command-> 메인에서 호출을 통해
한줄씩 입력 받아서 명령을 실행하도록 함

<<기능>>
1.load: 파일을 로드시킨다.
2.add:이름과 전화번호를 추가
3.find:이름으로 전화번호를 찾기
4.remover:이름으로 정보 삭제
(remove로 했다가 c에 관련 함수가
있어서 실패->바꿈)
5.save:파일에 저장
6.reallocate:공간이 부족해지면 재할당
7.status:상태를 보여줌

문제)계속 입력받지 않고 2번 입력받은후
프로그램이 종료된다
