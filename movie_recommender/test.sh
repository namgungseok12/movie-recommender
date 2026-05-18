#!/bin/bash

# 색상 정의
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}[1/3] 테스트용 데이터(CSV)를 설정하는 중...${NC}"
mkdir -p data

# 1. 영화 데이터 구축 (유사도 19점 피어가 추천할 영화 'Inception' 포함)
cat << 'EOF' > data/movies.csv
id,title,genre,releaseYear
1,Zootopia,Animation,2016
2,Aladdin,Animation,1992
3,Inception,Sci-Fi,2010
EOF

# 2. 사용자 데이터 구축 (대상: Jinny, 비교군: Tom, Bob)
cat << 'EOF' > data/users.csv
id,name,email
1,Jinny,jinny@ssu.ac.kr
2,Tom,tom@test.com
3,Bob,bob@test.com
EOF

# 3. 평점 데이터 구축 (유사도 수식: 공통 영화 수 * 10 - 평점 차이 합)
# - Jinny(1): 주토피아(5.0), 알라딘(4.0)
# - Tom(2)  : 주토피아(4.5), 알라딘(3.5), 인셉션(5.0) -> 공통 2개, 차이합 1.0 -> 20 - 1.0 = 19점!
# - Bob(3)  : 주토피아(2.0), 알라딘(1.0)             -> 공통 2개, 차이합 6.0 -> 20 - 6.0 = 14점!
cat << 'EOF' > data/ratings.csv
userId,movieId,score
1,1,5.0
1,2,4.0
2,1,4.5
2,2,3.5
2,3,5.0
3,1,2.0
3,2,1.0
EOF

echo -e "${BLUE}[2/3] 프로젝트를 빌드(컴파일)하는 중...${NC}"
make clean
make

if [ ! -f ./movie_recommender ]; then
    echo "❌ 빌드에 실패했습니다. 코드를 확인해 주세요."
    exit 1
fi

echo -e "${BLUE}[3/3] 추천 시스템 자동화 시나리오 테스트 시작...${NC}"
echo -e "${GREEN}▶ 입력 시나리오: 9번(추천) 선택 -> 'Jinny' 입력 -> 0번(종료)${NC}\n"

# 표준 입력을 통해 메뉴 9번 -> Jinny -> 종료 0번을 순서대로 주입합니다.
./movie_recommender << 'EOF'
9
Jinny
0
EOF

echo -e "\n${GREEN}🎉 테스트 스크립트 실행이 완료되었습니다!${NC}"