
# boj-solve

C++ and Python solutions for BOJ problems

## Problem source

[Baekjoon Online Judge](https://www.acmicpc.net)

## Environment

- Ubuntu 24.04.2 LTS
- g++ 13.3.0 with `-std=gnu++17`
- Python 3.12.3

## Checklist

inspired by [justiceHui's Unknown-To-Wellknown](https://github.com/justiceHui/Unknown-To-Wellknown)

### Berlekamp-Massey

[koosaga](https://koosaga.com/231) / [mzhang2021](https://mzhang2021.github.io/cp-blog/berlekamp-massey/)

  - [x] BOJ 13727 5차원 구사과 초콜릿

### Aliens Trick

[koosaga](https://koosaga.com/243) / [robert1003](https://robert1003.github.io/2020/02/26/dp-opt-wqs-binary-search.html) / [USACO Guide](https://usaco.guide/adv/lagrange)

  - [x] BOJ 19672 Feast
  - [x] BOJ 16191 Utilitarianism
  - [ ] BOJ 20090 Aliens
  - [x] BOJ 24442 수열 쪼개기
  - [ ] BOJ 14510 Blazing New Trails
  - [x] BOJ 17439 꽃집
  - [ ] BOJ 17823 수열과 쿼리 33
  - [ ] BOJ 18456 Jealous Split

### Slope Trick

[jwvg0425](https://jwvg0425-ps.tistory.com/98) / [koosaga](https://koosaga.com/243) / [USACO Guide](https://usaco.guide/adv/slope-trick) / [lobo_prix](https://blog.tuxedcat.com/all/algorithm/doc/dp/slope%20trick%201.html)

  - [x] BOJ 15773 Touch The Sky
  - [x] BOJ 13323 BOJ 수열 1
  - [x] BOJ 13324 BOJ 수열 2
  - [x] BOJ 2586 소방차
  - [x] BOJ 27345 Potatoes and fertilizers
  - [x] BOJ 19693 Safety
  - [x] BOJ 18720 Bookface
  - [x] BOJ 12736 Fireworks
  - [x] BOJ 12010 Landscaping

### Segment Tree Beats

[jiry_2](https://codeforces.com/blog/entry/57319) / [Errichto](https://youtu.be/wFqKgrW1IMQ) / [rdd6584](https://github.com/infossm/infossm.github.io/blob/7571d3d0ac66f7dd60f35cc4e826d20995ca1875/_posts/2019-10-19-Segment-Tree-Beats.md) / [koosaga](https://koosaga.com/307)

  - [x] BOJ 17474 수열과 쿼리 26
  - [ ] BOJ 14899 수열과 쿼리 19
  - [ ] BOJ 17476 수열과 쿼리 28
  - [ ] BOJ 19277 ADD, DIV, MAX
  - [ ] BOJ 17473 수열과 쿼리 25
  - [ ] BOJ 17477 수열과 쿼리 29
  - [ ] BOJ 17475 수열과 쿼리 27

### Kinetic Segment Tree

[koosaga](https://koosaga.com/307)

  - [ ] BOJ 2788 스타트업
  - [ ] BOJ 26144 꺾이지 않는 마음 3

### BBST (Splay Tree, Treap)

Splay Tree: [cubelover](https://cubelover.tistory.com/10) / [Zhtluo](https://zhtluo.com/cp/splay-tree-one-tree-to-rule-them-all.html)

Treap: [SecondThread](https://codeforces.com/blog/entry/84017)

  - [x] BOJ 16994 로프와 쿼리
  - [x] BOJ 9548 무제
  - [x] BOJ 13159 배열
  - [x] BOJ 3444 Robotic Sort
  - [x] BOJ 17607 수열과 쿼리 31
  - [x] BOJ 19589 카드 셔플
  - [ ] BOJ 13543 수열과 쿼리 2
  - [ ] BOJ 2844 자료 구조
  - [ ] BOJ 19497 Subtract if Greater!
  - [ ] BOJ 15389 Imelda’s Shopping Spree
  - [ ] BOJ 17486 수열과 쿼리 30

### Dynamic Tree (Link-Cut Tree, Euler Tour Tree, Top Tree)

Link-Cut Tree: [imeimi](https://imeimi.tistory.com/27)

  - [x] BOJ 13539 트리와 쿼리 11
  - [x] BOJ 21973 남극 탐험
  - [x] BOJ 10724 판게아 2
  - [ ] BOJ 18861 가슴 속에 무엇인가
  - [ ] BOJ 22906 장난감 오렌지 만들기
  - [ ] BOJ 18374 함수의 맛

Euler Tour Tree: [PurpleCrayon](https://codeforces.com/blog/entry/102087)

  - [ ] BOJ 27974 트리와 쿼리 21

Top Tree: [koosaga](https://github.com/infossm/infossm.github.io/blob/master/_posts/2021-03-21-toptree.md)

  - [ ] BOJ 17936 트리와 쿼리 13
  - [ ] BOJ 21728 트리와 2개의 지름

### Stern-Brocot Tree

[myungwoo](https://blog.myungwoo.kr/126)

  - [x] BOJ 22662 Pi is Three
  - [x] BOJ 1882 분수 찾기

### Permutation Tree

[errorgorn](https://codeforces.com/blog/entry/78898) / [OI-Wiki (Chinese)](https://oi-wiki.org/ds/divide-combine/)

  - [ ] BOJ 25503 순열 뒤집기
  - [ ] BOJ 23720 움얌얌

### Push Relabel Algorithm, Cost Scaling Algorithm

Push Relabel Algorithm: [koosaga](https://koosaga.com/287)

  - [x] BOJ 13161 분단의 슬픔

Cost Scaling Algorithm: [koosaga](https://koosaga.com/289)

  - [ ] BOJ 19022 Flow

### Dual of Planar Graph

[ahgus89](https://algoshitpo.github.io/2020/03/23/dual/)

  - [x] BOJ 13145 Masonry Bridge
  - [ ] BOJ 17442 삼분 그래프
  - [x] BOJ 15308 비밀 요원
  - [ ] BOJ 18941 평면그래프와 게임

### Dominator Tree

[jinhan814](https://blog.naver.com/jinhan814/222636375208) / [koosaga](https://koosaga.com/201) / [mhy908](https://lunarhy.tistory.com/11)

$O((V+E) \log V)$: [Baba](https://codeforces.com/blog/entry/22811)

  - [x] BOJ 19335 Increasing Costs
  - [ ] BOJ 20174 Ink Mix
  - [ ] BOJ 25424 School Road

### Directed MST

$O(VE)$: [gina0605](https://gina65.tistory.com/23)

$O((V+E) \log E)$: [koosaga](https://koosaga.com/265)

  - [x] BOJ 16127 미생물 키우기
  - [ ] BOJ 19264 Hung Fu
  - [ ] BOJ 9582 Dictionary

### Offline Incremental SCC

[cheetose](https://github.com/infossm/infossm.github.io/blob/master/_posts/2021-03-21-offline-incremental-SCC.md)

  - [x] BOJ 19028 Link Cut Diagraph
  - [x] BOJ 8496 Godzilla

### Chordal Graph

[ainta](https://github.com/infossm/infossm.github.io/blob/master/_posts/2019-04-20-Finding%20perfect%20elimination%20ordering%20in%20choral%20graphs.md)

  - [x] BOJ 16003 자석 장난감
  - [ ] BOJ 16365 Square Root

### Treewidth, Tree Decomposition

[koosaga](https://koosaga.com/295) / [Ignasi Sau](https://www.lirmm.fr/~sau/talks/tw-Ignasi-2021.pdf)

  - [ ] BOJ 16183 Electronic Circuit
  - [ ] BOJ 26415 Ghost
  - [ ] BOJ 22982 선인장의 독립집합
  - [ ] BOJ 17824 아폴로니안 네트워크
  - [ ] BOJ 19267 Kid's Nightmare
  - [ ] BOJ 11738 Distance on Triangulation
  - [ ] BOJ 17366 %
  - [ ] BOJ 27814 Emacs++
  - [ ] BOJ 17697 Railway Trip
  - [ ] BOJ 24710 Station
  - [ ] BOJ 25407 외곽 순환 도로

### General Graph Matching

[koosaga](https://koosaga.com/258)

  - [x] BOJ 15737 일반 그래프 매칭
  - [x] BOJ 21086 Smol Vertex Cover
  - [ ] BOJ 16661 Bimatching
  - [ ] BOJ 18447 Angle Beats
  - [ ] BOJ 15741 일반 그래프 최대 가중치 매칭
  - [ ] BOJ 21639 Cooking
  - [ ] BOJ 18519 Planar Max Cut

### Palindrome Tree (eerTree)

[Karuna](https://algoshitpo.github.io/2020/03/23/eertree/) / [Alessio Piergiacomi](https://medium.com/@alessiopiergiacomi/eertree-or-palindromic-tree-82453e75025b)

  - [ ] BOJ 10066 팰린드롬
  - [ ] BOJ 15893 가장 긴 공통부분 팰린드롬
  - [ ] BOJ 18285 Jaki Jovsi

### Suffix Automaton, Suffix Tree

[koosaga](https://koosaga.com/314)

  - [ ] BOJ 16907 서로 다른 부분 문자열 쿼리 2
  - [ ] BOJ 19515 Jong Hyok and String
  - [ ] BOJ 13541 K번째 부분 문자열
  - [ ] BOJ 26109 Longest Substring
  - [ ] BOJ 14436 서로 다른 부분 문자열 쿼리
  - [ ] BOJ 18544 Incomparable Pairs
  - [ ] BOJ 18349 천지창조

### Run Enumerate

[koosaga](https://codeforces.com/blog/entry/106725)

  - [ ] BOJ 23495 Longest Lyndon Prefix
  - [ ] BOJ 25111 Repetitions
  - [ ] BOJ 19020 Decomposition
  - [ ] BOJ 16284 Lucid Strings

### FFT, NTT, Convolution

[namnamseo](https://namnamseo.tistory.com/entry/FFT-in-competitive-programming) / [jhnah917](https://algoshitpo.github.io/2020/05/20/fft-ntt/)

  - [x] BOJ 22289 큰 수 곱셈 (3)
  - [x] BOJ 10531 Golf Bot
  - [x] BOJ 1067 이동
  - [x] BOJ 13575 보석 가게
  - [x] BOJ 11385 씽크스몰
  - [x] BOJ 14882 다항식과 쿼리
  - [x] BOJ 13428 배열의 합
  - [x] BOJ 14176 트리와 소수

### Linear Recurrence by Polynomials

Kitamasa: [jhnah917](https://justicehui.github.io/hard-algorithm/2021/03/13/kitamasa/)

Bostan-Mori: [myungwoo](https://blog.myungwoo.kr/149)

  - [x] BOJ 15572 블록 4
  - [x] BOJ 13725 RNG
  - [x] BOJ 13178 목공

### Sum Over Subsets DP, FWHT

[gina0605](https://gina65.tistory.com/30) / [upobir](https://codeforces.com/blog/entry/71899)

  - [x] BOJ 2803 내가 어렸을 때 가지고 놀던 장난감
  - [x] BOJ 14878 부분 수열 XOR합
  - [x] BOJ 13758 RNG 2
  - [x] BOJ 25563 AND, OR, XOR

### Multipoint Evaluation

Polynomial Division: [hyperbolic](https://hyperbolic.tistory.com/4) / [cubelover](https://cubelover.tistory.com/22)

[ho94949](https://github.com/infossm/infossm.github.io/blob/master/_posts/2019-06-17-Multipoint-evaluation.md) / [hyperbolic](https://hyperbolic.tistory.com/5)

  - [x] BOJ 18168 Game with Polynomials 2

### Generating Function

[evenharder](https://github.com/infossm/infossm.github.io/blob/master/_posts/2019-10-19-generating-function.md)

[yclock - 1](https://github.com/infossm/infossm.github.io/blob/master/_posts/2021-04-18-generating-functions-1.md), [yclock - 2](https://github.com/infossm/infossm.github.io/blob/master/_posts/2021-05-17-generating-functions-2.md)

  - [ ] BOJ 13542 우표 구매하기 (Hard)
  - [ ] BOJ 26037 지수 · 로그와 테일러 다항식(Large)

### Mobius Inversion

[rkm0959 - 1](https://rkm0959.tistory.com/186), [rkm0959 - 2](https://rkm0959.tistory.com/184)

[snowflake - 1](https://xy-plane.tistory.com/16), [snowflake - 2](https://xy-plane.tistory.com/17), [snowflake - 3](https://xy-plane.tistory.com/18), [snowflake - 4](https://xy-plane.tistory.com/19)

[ahgus89](https://ahgus89.github.io/algorithm/M%C3%B6bius-inversion/)

  - [x] BOJ 16409 Coprime Integers
  - [x] BOJ 11691 LCM(i, j)
  - [x] BOJ 14861 LCM 더하기

### Young Tableau Diagram, RSK Correspondence

[mango_lassi](https://codeforces.com/blog/entry/98167) / [yclock](https://youngyojun.github.io/secmem/2021/09/19/young-tableaux/)

  - [ ] BOJ 18594 Three Investigators
  - [ ] BOJ 18461 Disjoint LIS

### Matroid Intersection

[ainta - 1](https://github.com/infossm/infossm.github.io/blob/master/_posts/2019-05-08-introduction-to-matroid.md), [ainta - 2](https://github.com/infossm/infossm.github.io/blob/master/_posts/2019-06-17-Matroid-Intersection.md) / [ATSTNG](https://codeforces.com/blog/entry/69287) / [imeimi](https://imeimi.tistory.com/45)

  - [x] BOJ 3836 Coin Collecting
  - [x] BOJ 16046 Rainbow Graph
  - [x] BOJ 18517 Pick Your Own Nim
  - [ ] BOJ 18890 Seollal
  - [ ] BOJ 21727 아즈텍의 섬
  - [ ] BOJ 23052 두 트리

### LGV Lemma

[miaowtin](https://codeforces.com/blog/entry/108395) / [OI-Wiki (Chinese)](https://oi-wiki.org/graph/lgv/)

  - [ ] BOJ 19514 Intersection is Not Allowed!
  - [ ] BOJ 24670 Mountains
  - [ ] BOJ 21265 Ascending Matrix

### Voronoi Diagram, Delaunay Triangulation

  - [ ] BOJ 15695 Panda Preserve
  - [ ] BOJ 21065 Friendship Circles
  - [ ] BOJ 5401 Escape from the Minefield
  - [ ] BOJ 18349 천지창조

### Minkovski Sum DP

[arnold518](https://arnold518.tistory.com/72)

  - [ ] BOJ 17674 특별관광도시
  - [ ] BOJ 18477 Jiry Matchings

### Regions Trick (Query Caching)

[jhnah917](https://github.com/justiceHui/SSU-SCCC-Study/blob/master/2022-winter-adv/slide/01.pdf)

  - [ ] BOJ 12857 홍준이는 문자열을 좋아해
  - [ ] BOJ 25952 Rectangles
  - [ ] BOJ 22316 Regions
  - [ ] BOJ 25504 최적 경로와 쿼리
  - [ ] BOJ 25505 공통 부분 문자열 쿼리

### Bulldozer Trick

[jhnah917](https://github.com/justiceHui/SSU-SCCC-Study/blob/master/2022-winter-adv/slide/05.pdf)

  - [x] BOJ 9484 최대삼각형, 최소삼각형
  - [x] BOJ 3121 빨간점, 파란점
  - [x] BOJ 16783 Bulldozer
  - [ ] BOJ 17973 Quadrilaterals
  - [ ] BOJ 17739 Constellation 2
  - [x] BOJ 17625 고압선

### Query Buckets

[jhnah917](https://github.com/justiceHui/SSU-SCCC-Study/blob/master/2022-winter-adv/slide/01.pdf)

  - [ ] BOJ 17635 다리
  - [ ] BOJ 5823 코끼리
  - [ ] BOJ 18254 쿼리와 쿼리
  - [ ] BOJ 16793 Collapse

### Segment Tree Graph

[jhnah917](https://justicehui.github.io/tutorial/2020/09/05/graph-with-segment-tree/)

  - [x] BOJ 18193 비행기 타고 가요
  - [ ] BOJ 25946 Flags
  - [ ] BOJ 8274 Journeys
  - [ ] BOJ 18362 Desert

### Tangents on Convex Polygons

[jhnah917](https://github.com/justiceHui/SSU-SCCC-Study/blob/master/2022-autumn-adv/slide/05.pdf)

  - [ ] BOJ 15310 아티스트
  - [ ] BOJ 5257 timeismoney
  - [ ] BOJ 25009 뚫기

### Escape Trick (Exchange Argument on Trees)

[koosaga](https://koosaga.com/349) / [maspy (Japanese)](https://maspypy.com/01-on-tree-%e4%ba%ac%e9%83%bd%e8%a6%b3%e5%85%89-train-seats)

  - [ ] BOJ 9539 Escape
  - [ ] BOJ 18596 Monster Hunter
  - [ ] BOJ 17590 Prospecting
  - [ ] BOJ 1763 트리 색칠

### Fast I/O

[cgiosy](https://cgiosy.github.io/posts/fast-io)

  - [ ] BOJ 11921 0.1
  - [ ] BOJ 18702 Array Queries (cf. BOJ 17476 수열과 쿼리 28)

### Bitset Optimization

[Errichto](https://codeforces.com/blog/entry/73558)

  - [ ] BOJ 20501 Facebook
  - [ ] BOJ 9423 레슬링 팀 선발
  - [ ] BOJ 9789 Friendship Graph - $O(N^3/w)$
  - [ ] BOJ 23373 Jack the Mole - $O(N^3W/w)$
  - [ ] BOJ 17184 Nautilus
  - [ ] BOJ 18439 LCS 6

### SIMD

[jhnah917](https://justicehui.github.io/hard-algorithm/2021/11/15/simd-in-ps/)

  - [ ] BOJ 14438 수열과 쿼리 17 - $O(Q \log N)$ vs $O(NQ/8)$
  - [ ] BOJ 3847 Comparing answers - $O(N^2)$ vs $O(N^3/8)$
  - [ ] BOJ 13925 수열과 쿼리 13 - $O(Q \log N)$ vs $O(NQ/8)$
  - [ ] BOJ 23577 Trio - $O(81N^2)$ vs $O(N^3/96)$ vs $O(20000N^2/512)$

### Barrett Reduction

[Spheniscine](https://codeforces.com/blog/entry/75406)

  - [x] BOJ 17467 N! mod P (2)

### Chirp Z-Transform

  - [x] BOJ 18354 다항식과 쿼리 2

### Gradient Descent

  - [x] BOJ 19352 Factory
  - [x] BOJ 4360 A star not a Tree?
  - [x] BOJ 11930 Smallest Enclosing Sphere
  - [x] BOJ 13408 Cover the Polygon with Your Disk

### Half Plane Intersection

  - [ ] BOJ 3903 제주도
  - [ ] BOJ 3527 Jungle Outpost

### Hungarian, Dual Linear Program

  - [x] BOJ 14216 할 일 정하기 2
  - [x] BOJ 1281 보석상
  - [x] BOJ 19043 Balance
  - [x] BOJ 13091 Longest Shortest Path

### Lagrange Interpolation

  - [x] BOJ 27293 거듭제곱의 합 2
  - [x] BOJ 17468 N! mod P (3)

### Shamos-Hoey

  - [x] BOJ 20150 선분 교차 4
  - [x] BOJ 17196 Cow Steeplechase II
  - [x] BOJ 6620 Simple Polygon
  - [x] BOJ 20151 선분 교차 5

### Eulerian Path/Circuit

  - [x] BOJ 1591 수열 복원
  - [x] BOJ 1616 드럼통 메시지

### System of Difference Constraints

  - [x] BOJ 7040 밥 먹기
  - [x] BOJ 7577 탐사
  - [x] BOJ 2081 저울추

### KMP + Segment Tree (Extended KMP?)

  - [x] BOJ 23576 Stock Price Prediction
  - [x] BOJ 20298 파인애플 피자

### Stoer-Wagner (Global Minimum Cut)

  - [x] BOJ 13367 Weeping Fig
  - [x] BOJ 14060 Paths in Multigraph

### Fast Graph Traversal with Segment Tree

  - [x] BOJ 13988 비무장 지대
  - [x] BOJ 11915 전선 연결하기

### Discrete Square Root

  - [x] BOJ 17603 Factorization

### Rerooting

  - [x] BOJ 7812 중앙 트리
  - [x] BOJ 27730 견우와 직녀
  - [ ] BOJ 22900 나의 라임 오렌지 나무
  - [ ] BOJ 14875 City Attractions

### Connection Profile DP

  - [x] BOJ 1144 싼 비용
  - [ ] BOJ 2850 배관공 김선영
  - [ ] BOJ 19573 꿀벌

### Mertens Trick

  - [ ] BOJ 16123 피타고라스 쌍
  - [ ] BOJ 16141 정수론과 응용: 레시테이션
  - [ ] BOJ 16644 Easy Problem

### Min-Cost Flow + Priority Queue

  - [x] BOJ 1150 백업
  - [x] BOJ 29772 병사 분배
  - [x] BOJ 19654 Sequence
  - [ ] BOJ 32157 한요원의 잠입
  - [ ] BOJ 11848 Schools

### Second MST

  - [x] BOJ 15481 그래프와 MST
  - [x] BOJ 1626 두 번째로 작은 스패닝 트리
  - [x] BOJ 10637 Minimum Spanning Tree
  - [x] BOJ 10169 안전한 비상연락망

### Connected Component DP

  - [x] BOJ 21213 Mentors
  - [x] BOJ 13188 Kangaroo
  - [x] BOJ 16781 Skyscraper
