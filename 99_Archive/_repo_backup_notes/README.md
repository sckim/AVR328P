# 유실 위험 저장소 백업 — 2026-09-20 10:55

원격을 GitHub에서 찾을 수 없어(Repository not found) 로컬이 유일본일 수 있는 저장소들이다.
복원: git clone <name>.bundle <폴더명>

## Arduino_BP6A_EVK
- 로컬 경로: Atmega328P\01_Arduino_Projects\15_Integrated_Projects\02_Projects\Arduino\BP6A\Arduino_BP6A_EVK
- 원격(없음): https://github.com/sckim/Arduino_BP6A_EVK.git
- 브랜치: main, refs 3개, 커밋 32개
- 번들: Arduino_BP6A_EVK.bundle (63.2 MB), 검증 FAIL
- 미커밋 변경: 4건 (패치 저장됨)

## bp6a_serial_analyzer
- 로컬 경로: Atmega328P\01_Arduino_Projects\15_Integrated_Projects\02_Projects\Arduino\BP6A\bp6a_serial_analyzer
- 원격(없음): https://github.com/Life-Science-Technology/bp6a_serial_analyzer.git
- 브랜치: main, refs 7개, 커밋 43개
- 번들: bp6a_serial_analyzer.bundle (0.1 MB), 검증 FAIL
- 미커밋 변경: 4건 (패치 저장됨)

## Arduino_examples
- 로컬 경로: Atmega328P\01_Arduino_Projects\15_Integrated_Projects\Arduino_Examples
- 원격(없음): https://github.com/sckim/Arduino_examples.git
- 브랜치: editing, refs 5개, 커밋 47개
- 번들: Arduino_examples.bundle (0.2 MB), 검증 FAIL
- 미커밋 변경: 2건 (패치 저장됨)

## Demo
- 로컬 경로: Atmega328P\01_Arduino_Projects\99_Archive\Arduino_Sketch\Demo
- 원격(없음): https://github.com/sckim/Demo.git
- 브랜치: main, refs 3개, 커밋 3개
- 번들: Demo.bundle (0.0 MB), 검증 FAIL
- 미커밋 변경: 0건

## uC_examples
- 로컬 경로: Atmega328P\02_AVR_C_Development\99_Archive\99_Archive\Native_C\uC_examples
- 원격(없음): https://github.com/sckim/uC_examples.git
- 브랜치: HEAD, refs 2개, 커밋 개
- 번들: uC_examples.bundle (0.0 MB), 검증 FAIL
- 미커밋 변경: 249건 (패치 저장됨)
## 검증 결과 (재확인)
- Arduino_BP6A_EVK.bundle : verify OK, complete history
- bp6a_serial_analyzer.bundle : verify OK, complete history
- Arduino_examples.bundle : verify OK, complete history
- Demo.bundle : verify OK, complete history

## uC_examples — 주의
- git 저장소가 손상되었다. 객체 저장소가 비어 있고(0 objects) blob 182개가 없다.
- refs/remotes/origin/master, sckim-patch-1 가 가리키는 커밋을 복원할 수 없다.
- 따라서 히스토리는 보존 불가. 작업 트리 파일만 uC_examples_working_files.zip 으로 보관했다.
- 미커밋 상태 249건은 uC_examples_status.txt 참고.

## 복원 방법
- 번들: git clone <name>.bundle <새폴더>
- 압축: 그냥 풀면 된다 (git 히스토리 없음)