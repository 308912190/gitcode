//
// Created by hazyparker on 2021/12/9.
//

#include "AStarSearch.h"
#include "readMap.h"
#include "cmath"
#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <vector>
#include <utility>
#include <opencv2/opencv.hpp>

using namespace std;

typedef pair<int, int> Pair;
typedef tuple<double, int, int> Tuple;
typedef vector<vector<int>> Vec2int;

struct Compare {
    double p;  // 用来调整最小和最长代价的系数

    Compare(double p_value) : p(p_value) {}

    bool operator()(const Tuple& a, const Tuple& b) {
        double g_a = get<0>(a);  // 当前路径的代价
        double h_a = get<1>(a);  // 启发式代价

        double g_b = get<0>(b);
        double h_b = get<1>(b);

        double f_a = g_a + p * h_a;
        double f_b = g_b + p * h_b;

        if (f_a == f_b) {
            double h_ratio_a = g_a / h_a;  // 计算最小与最长代价的比值
            double h_ratio_b = g_b / h_b;
            return h_ratio_a > h_ratio_b;
        }

        return f_a > f_b;
    }
};
AStar::AStar() {
    // constructor function
    mapPath = "../../maps/test_1.map";

    StartPoint = {10, 10};
    EndPoint = {90, 90};
    ROW = 100;
    COL = 100;

    rawMap = imread("../images/test.jpg");
}

Pair AStar::cor2ArrayPos(Pair corPos) {
    Pair ArrayPos;
    ArrayPos.first = corPos.second - 1;
    ArrayPos.second = corPos.first - 1;
    return ArrayPos;
}

Pair AStar::array2CorPos(Pair arrayPos) {
    Pair corPos;
    corPos.first = arrayPos.second + 1;
    corPos.second = arrayPos.first + 1;
    return corPos;
}

void AStar::setStartPoint(int x, int y) {
    Pair corPos;
    corPos.first = x;
    corPos.second = y;

    StartPoint = cor2ArrayPos(corPos);
}

void AStar::setEndPoint(int x, int y) {
    Pair corPos;
    corPos.first = x;
    corPos.second = y;

    EndPoint = cor2ArrayPos(corPos);
}

bool AStar::isValid(const vector<vector<int>> &grid, const Pair &point) const {
    // Returns true if row number and column number is in range
    if (ROW > 0 && COL > 0)
        return (point.first >= 0) && (point.first < ROW)
               && (point.second >= 0)
               && (point.second < COL);

    else return false;
}

bool AStar::isUnBlocked(const vector<vector<int>> &grid, const Pair &point) const {
    // Returns true if the cell is not blocked else false
    return isValid(grid, point)
           && grid[point.first][point.second] == 1;
}

bool AStar::isDestination(const Pair &position) {
    return position == EndPoint;
}

double AStar::calculateHValue(const Pair &src, const Pair &dest) {
    // h is estimated with the two points distance formula
    return sqrt(pow((src.first - dest.first), 2.0)
                + pow((src.second - dest.second), 2.0));
}

void AStar::aStarSearch(){
    binaryObstacleMap = getBinaryEdgeMap();
    vector<vector <int>> grid;
    grid = mat2Vector(binaryObstacleMap, ROW, COL);
    // set begin time
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    // If the source is out of range
    if (!isValid(grid, StartPoint)) {
        printf("Source is invalid\n");
        return;
    }

    // If the destination is out of range
    if (!isValid(grid, EndPoint)) {
        printf("Destination is invalid\n");
        return;
    }

    // Either the source or the destination is blocked
    if (!isUnBlocked(grid, StartPoint)
        || !isUnBlocked(grid, EndPoint)) {
        printf("Source or the destination is blocked\n");
        return;
    }

    // If the destination cell is the same as source cell
    if (isDestination(StartPoint)) {
        printf("We are already at the destination\n");
        return;
    }

    // describe detail of each cell
    // using struct defined
    vector<vector <cell>> cellDetails(ROW, vector<cell>(COL));

    int i, j;
    // Initialising the parameters of the starting node
    i = StartPoint.first, j = StartPoint.second;
    cellDetails[i][j].cost_f = 0.0;
    cellDetails[i][j].cost_g = 0.0;
    cellDetails[i][j].cost_h = 0.0;
    cellDetails[i][j].nodeParent = {i, j};

    // Create a closed list and initialise it to false
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    /**
     * Create an open list having information as <f, <i, j>>
     * where f = g + h,
     * and i, j are the row and column index of that cell
     * Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
     * This open list is implemented as a set of tuple
     */
    priority_queue<Tuple, vector<Tuple>,Compare> openList(Compare(2.0));
    // Type: Tuple
    // Container: vector
    // Functional: greater, least f will be on top of the queue

    openList.emplace(0.0, i, j);
    while(!openList.empty()){
        const Tuple& p = openList.top(); // first time, it will be start point
        // Add this vertex to the closed list
        i = get<1>(p); // second element of tuple
        j = get<2>(p); // third element of tuple

        // remove this vertex from open list and send it to close list
        openList.pop();
        closedList[i][j] = true;

        printf("parent node now:(%d, %d)\n", i, j);

        for (int add_x = -1; add_x <= 1; add_x++) {
            for (int add_y = -1; add_y <= 1; add_y++) {

                printf("added vector now:(%d, %d)\n", i + add_x, j + add_y);

                Pair neighbour(i + add_x, j + add_y);

                if (!isValid(grid, neighbour)){
                    cout << neighbour.first << ", " << neighbour.second << "is invalid";
                    return;
                }
                if (isDestination(neighbour)){
                    // set parent of destination cell
                    cellDetails[neighbour.first][neighbour.second].nodeParent = {i, j};
                    // print path
                    cout << "destination is found!" << endl;
                    tracePath(cellDetails);
                    // set end time and show
                    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
                    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
                    cout << "solve time cost = " << time_used.count() << " seconds. " << endl;
                    // end
                    return;
                }
                else if (!closedList[neighbour.first][neighbour.second]
                         && isUnBlocked(grid, neighbour)){

                    printf("(%d, %d) will be calculated\n", neighbour.first, neighbour.second);

                    // update weight values
                    double f_updated, g_updated, h_updated;
                    g_updated = cellDetails[i][j].cost_g + sqrt(pow(add_x, 2.0) + pow(add_y, 2.0));
                    h_updated = calculateHValue(neighbour, EndPoint);
                    f_updated = g_updated + h_updated;

                    // send less f_updated to open list
                    double temp_cost_f = cellDetails[neighbour.first][neighbour.second].cost_f;
                    if (f_updated < temp_cost_f || temp_cost_f == -1){
                        // -1 referring that this node doesn't belong to open list, shall be added in
                        // f_updated is less, shall be added in open list
                        // at first I was concerning about the StartPoint, then I just realized that
                        // StartPoint has been thrown into close list
                        openList.emplace(f_updated, neighbour.first, neighbour.second);

                        printf("(%d, %d) added to open list\n", neighbour.first, neighbour.second);

                        // update cost f, g, h and parent node of cellDetails
                        cellDetails[neighbour.first][neighbour.second].cost_f = f_updated;
                        cellDetails[neighbour.first][neighbour.second].cost_g = g_updated;
                        cellDetails[neighbour.first][neighbour.second].cost_h = h_updated;
                        // set parent of successors(not in Close list and is unblocked)
                        cellDetails[i + add_x][j + add_y].nodeParent = {i, j};
                        /**
                         * why updating parent node must exist here?
                         * if you actually put this update under definition of neighbour, some path might be confusing
                         * set updating here can assure that each node parent heading for gradient lifting
                         * namely f in decline
                         */
                    }

                }

            }

        }

    }

}

void AStar::tracePath(const vector<vector<cell>> &cellDetails) {
    /**
     * there must be a circle
     * until cellDetails[][].nodeParent = StartPoint
     * we shall start from EndPoint, getting its parent, test the condition above
     * then go into next loop
     */
    int i = EndPoint.first;
    int j = EndPoint.second;
    Pair temp_node;
    while(cellDetails[i][j].nodeParent != StartPoint){
        Path.push({i, j});
        temp_node = cellDetails[i][j].nodeParent;
        // i = cellDetails[i][j].nodeParent.first is illegal!
        i = temp_node.first;
        j = temp_node.second;
    }
    // push StartPoint into Stack
    Path.push(StartPoint);
}

void AStar::drawPath() {
    ObstacleMap = readMap(mapPath);
    Mat pathImg;
    ObstacleMap.copyTo(pathImg);
    cvtColor(pathImg, pathImg, COLOR_GRAY2BGR);

    // set path color, BGR order
    Vec3b pathColor;
    pathColor[0] = 0;
    pathColor[1] = 255;
    pathColor[2] = 0;

    Vec3b startColor = {0, 0, 255};

    Vec3b endColor = {255, 0, 0};

    // draw start and end point
    pathImg.at<Vec3b>(StartPoint.first, StartPoint.second) = startColor;
    pathImg.at<Vec3b>(EndPoint.first, EndPoint.second) = endColor;

    // form window
    namedWindow("Obstacle map", WINDOW_NORMAL);
    namedWindow("path on map", WINDOW_NORMAL);

    int i, j;
    Pair p_cor;
    while (!Path.empty()) {
        Pair p = Path.top();
        Path.pop();
        i = p.first;
        j = p.second;
        p_cor = array2CorPos(p);
        printf("(%d, %d)->\n", p_cor.first, p_cor.second);
        pathImg.at<Vec3b>(i, j) = pathColor;
        pathImg.at<Vec3b>(StartPoint.first, StartPoint.second) = startColor;
        pathImg.at<Vec3b>(EndPoint.first, EndPoint.second) = endColor;
        imshow("path on map", pathImg);
        waitKey(100);
    }

    imshow("Obstacle map", ObstacleMap);
    waitKey(0);

    imwrite("../images/path1.jpg", pathImg);
}

Mat AStar::readMap(const string &filename) {
    int32_t m_mx, m_my, m_startX, m_startY, m_endX, m_endY;
    int8_t *m_map;
    Mat img ,dst;

    FILE        *fp;
    uint32_t    f_magic;

    // open file
    const char *filepath = (char*)filename.data();
    fp = fopen(filepath, "rb");
    if( fp == nullptr ) {
        printf("ERR: failed to open file %s!\n", filepath);
        exit(100);
    }

    // check file magic number
    fread(&f_magic, sizeof(uint32_t), 1, fp);
    if( f_magic != 0x15432345 ) {
        printf("ERR: input file format is not correct! %s\n", filepath);
        goto MAP_LOAD_RET;
    }

    // read map nx, ny
    fread(&m_mx, sizeof(int32_t), 1, fp);
    fread(&m_my, sizeof(int32_t), 1, fp);

    // read map
    m_map = new int8_t[m_mx * m_my];
    fread(m_map, sizeof(int8_t), m_mx * m_my, fp);

    // read start,end point
    fread(&m_startX, sizeof(int32_t), 1, fp);
    fread(&m_startY, sizeof(int32_t), 1, fp);
    fread(&m_endX, sizeof(int32_t), 1, fp);
    fread(&m_endY, sizeof(int32_t), 1, fp);

    MAP_LOAD_RET:
    fclose(fp);

    int cols = m_mx;
    int rows = m_my;
    img = Mat(rows, cols, CV_8U, Scalar::all(255));

    // convert m_map to int, sending to img
    for (int i = 0; i < cols; i++){
        for (int j = 0; j < rows; j++){
            img.at<uchar>(i, j) = int(m_map[i * cols + j]) * 255;
        }
    }

    // LUT
    uchar lutData[256];
    for (int i = 0; i < 256; ++i){
        lutData[i] = 255 - i;
    }
    Mat lutTable(1,256, CV_8U);
    uchar *p = lutTable.ptr();
    for (int i = 0; i < 256; ++i){
        p[i] = lutData[i];
    }

    LUT(img, lutTable, img);

    // erode, showing the edge
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    erode(img, dst, element);

    // uplift the gray scale of edges
    for (int i = 0; i < cols; i++){
        for (int j = 0; j < rows; j++){
            if(int(dst.at<uchar>(i, j)) == 0)
                dst.at<uchar>(i, j) = 200;
        }
    }

    // blend two images, using lower gray scale
    // consider using addWeight()
    for (int i = 0; i < cols; i++){
        for (int j = 0; j < rows; j++){
            if(int(dst.at<uchar>(i, j)) == 200 && int(img.at<uchar>(i, j)) == 0)
                dst.at<uchar>(i, j) = 0;
        }
    }

    dst.copyTo(ObstacleMap);
    return ObstacleMap;
}

void AStar::setMapName(const string& filename) {
    mapPath = "../../maps/" + filename;
}

Mat AStar::getBinaryEdgeMap() {
    ObstacleMap = readMap(mapPath);
    Mat src = ObstacleMap;
    /**
     * if src.at = 1, it's free to go
     * if src.at = 0, it's blocked
     */
    for (int i = 0; i < 100; i++){
        for (int j = 0; j < 100; j++){
            if(src.at<uchar>(i, j) != 255) src.at<uchar>(i, j) = 0;
            if(src.at<uchar>(i, j) == 255) src.at<uchar>(i, j) = 1;
        }
    }
    return src;
}

vector<vector <int>> AStar::mat2Vector(Mat &src, int m, int n) {
    vector<vector <int>> transferredVector(m, vector<int>(n));
    vector<int> flatVector= src.reshape(1,1);
    // FIXME: how to transfer Mat to vector<vector>
//    transferredVector = flatVector.resize(m, 0);
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            transferredVector[i][j] = int(src.at<uchar>(i, j));
        }
    }
    return transferredVector;
}

void AStar::openLidar(Pair pos) {
    vector<vector <int>> grid = getGridMap();
    int pos_i = pos.first;
    int pos_j = pos.second;

    int radius = 10;

    Mat img = imread("../images/test.jpg", IMREAD_COLOR);
    if (img.empty()){
        cout << "loading failed.." << endl;
        exit(100);
    }else{
        cout << "load successfully..." << endl;
    }
    Vec3b unseenColor = {0, 0, 255};
    Vec3b centerColor = {255, 0, 0};
    Vec3b obstacleColor = {0, 255, 0};

    pair<double, double> range;
    vector<pair<double, double>> degreeInterval;
    int i, j;
    for (int r = 1; r <= radius; r++){
        for (i = pos_i - r; i <= pos_i + r; i++){
            // case 1
            j = pos_j + (r - abs(i - pos_i));

            if (grid[i][j] == 1 || grid[i][pos_j - (r - abs(i - pos_i))] == 1) continue;
            printf("(%d, %d) is obstacle and being checked...\n", i, j);
            // get range
            range = getThetaRange(pos, {i, j});
            if (checkInterval(range, degreeInterval)){
                img.at<Vec3b>(i, j) = unseenColor;
            }else{
                img.at<Vec3b>(i, j) = obstacleColor;
            }
            mergeInterval(range, degreeInterval);

            // case 2
            j = pos_j - (r - abs(i - pos_i));
            printf("(%d, %d) is obstacle and being checked...\n", i, j);
            // get range
            range = getThetaRange(pos, {i, j});
            if (checkInterval(range, degreeInterval)){
                img.at<Vec3b>(i, j) = unseenColor;
            }else{
                img.at<Vec3b>(i, j) = obstacleColor;
            }
            mergeInterval(range, degreeInterval);
        }

    }

    for (int n = 0; n < degreeInterval.size(); n++){
        cout << degreeInterval[i].first << ", " << degreeInterval[i].second << endl;
    }

    namedWindow("radar", WINDOW_NORMAL);
    img.at<Vec3b>(pos_i, pos_j) = centerColor;
    imshow("radar", img);
    waitKey(0);

}

vector<vector<int>> AStar::getGridMap() {
    int32_t m_mx, m_my, m_startX, m_startY, m_endX, m_endY;
    int8_t *m_map;
    Mat img;

    FILE        *fp;
    uint32_t    f_magic;

    // open file
    const char* filepath = (char*)mapPath.data();
    fp = fopen(filepath, "rb");
    if( fp == nullptr ) {
        printf("ERR: failed to open file %s!\n", filepath);
        exit(100);
    }

    // check file magic number
    fread(&f_magic, sizeof(uint32_t), 1, fp);
    if( f_magic != 0x15432345 ) {
        printf("ERR: input file format is not correct! %s\n", filepath);
        goto MAP_LOAD_RET;
    }

    // read map nx, ny
    fread(&m_mx, sizeof(int32_t), 1, fp);
    fread(&m_my, sizeof(int32_t), 1, fp);

    // read map
    m_map = new int8_t[m_mx * m_my];
    fread(m_map, sizeof(int8_t), m_mx * m_my, fp);

    // read start,end point
    fread(&m_startX, sizeof(int32_t), 1, fp);
    fread(&m_startY, sizeof(int32_t), 1, fp);
    fread(&m_endX, sizeof(int32_t), 1, fp);
    fread(&m_endY, sizeof(int32_t), 1, fp);

    MAP_LOAD_RET:
    fclose(fp);

    int cols = m_mx;
    int rows = m_my;
    img = Mat(rows, cols, CV_8U, Scalar::all(255));

    // convert m_map to int, sending to img
    for (int i = 0; i < cols; i++){
        for (int j = 0; j < rows; j++){
            img.at<uchar>(i, j) = int(m_map[i * cols + j]);
        }
    }

    // Mat to Vector2int
    vector<vector <int>> grid(m_mx, vector<int>(m_my));
    for (int i = 0; i < m_mx; i++){
        for (int j = 0; j < m_my; j++){
            // 1 is reachable
            // 0 is blocked
            if (int(img.at<uchar>(i, j)) == 0) grid[i][j] = 1;
            if (int(img.at<uchar>(i, j)) == 1) grid[i][j] = 0;
        }
    }

    return grid;
}

pair<double, double> AStar::getThetaRange(Pair point_0, Pair point_d) {
    double PI = 3.1415926;
    pair<double, double> range;

    int i_0 = point_0.first;
    int j_0 = point_0.second;
    int i_d = point_d.first;
    int j_d = point_d.second;

    // save theta
    double theta[4] = {0, 0, 0, 0};
    // range change from (-PI, PI) to (0, 2PI)
    // FIXME: special definition around -PI
    theta[0] = atan2(i_d + 0.5 - i_0, j_d + 0.5 - j_0) * 180 / PI + 180;
    theta[1] = atan2(i_d + 0.5 - i_0, j_d - 0.5 - j_0) * 180 / PI + 180;
    theta[2] = atan2(i_d - 0.5 - i_0, j_d + 0.5 - j_0) * 180 / PI + 180;
    theta[3] = atan2(i_d - 0.5 - i_0, j_d - 0.5 - j_0) * 180 / PI + 180;
    sort(theta, theta + 4);
    // if theta[3] >= 315, i_0 == i_d (for sure)

    // send to pair range
    range.second = theta[3];
    range.first = theta[0];

    if (theta[3] > 340 && theta[0] < 19){
        range.second = theta[2];
        range.first = theta[1];
    }

    return range;
}

vector<pair<double, double>> AStar::mergeInterval(const pair<double, double> &newRange,
                                                  vector<pair<double, double>> &intervals) {
    // https://leetcode-cn.com/problems/merge-intervals/solution/he-bing-qu-jian-by-leetcode-solution/
    if (intervals.empty()) {
        return {};
    }

    intervals.emplace_back(newRange);

    sort(intervals.begin(), intervals.end());
    vector<pair<double, double>> merged;
    for (auto & interval : intervals) {
        double L = interval.first, R = interval.second;

        if (merged.empty() || merged.back().second < L) {
            merged.emplace_back(L, R);
        }
        else {
            merged.back().second = max(merged.back().second, R);
        }
    }
    return merged;
}

bool AStar::checkInterval(const pair<double, double> &newRange,
                          vector<pair<double, double>> &intervals) {
    bool value = false;
    if (intervals.empty()){
        return false;
    }

    sort(intervals.begin(), intervals.end());
    double left = newRange.first;
    double right = newRange.second;

    for (auto & interval : intervals){
        if (left >= interval.first && right <= interval.second){
            value = true;
            break;
        }
    }
    return value;
}

Vec2int AStar::getVector2intMap() {
    /**
     * 1 reachable
     * 0 blocked
     */
    const char *filepath = (char*)mapPath.data();

    // read map
    int32_t m_mx, m_my, m_startX, m_startY, m_endX, m_endY;
    int8_t *m_map;
    Mat img;

    FILE        *fp;
    uint32_t    f_magic;

    // open file
    fp = fopen(filepath, "rb");
    if( fp == nullptr ) {
        printf("ERR: failed to open file %s!\n", filepath);
        exit(100);
    }

    // check file magic number
    fread(&f_magic, sizeof(uint32_t), 1, fp);
    if( f_magic != 0x15432345 ) {
        printf("ERR: input file format is not correct! %s\n", filepath);
        goto MAP_LOAD_RET;
    }

    // read map nx, ny
    fread(&m_mx, sizeof(int32_t), 1, fp);
    fread(&m_my, sizeof(int32_t), 1, fp);
    ROW = m_mx;
    COL = m_my;

    // read map
    m_map = new int8_t[m_mx * m_my];
    fread(m_map, sizeof(int8_t), m_mx * m_my, fp);

    // read start,end point
    fread(&m_startX, sizeof(int32_t), 1, fp);
    fread(&m_startY, sizeof(int32_t), 1, fp);
    fread(&m_endX, sizeof(int32_t), 1, fp);
    fread(&m_endY, sizeof(int32_t), 1, fp);

    MAP_LOAD_RET:
    fclose(fp);

    int cols = m_mx;
    int rows = m_my;
    img = Mat(rows, cols, CV_8U, Scalar::all(255));

    // convert m_map to int, sending to img
    for (int i = 0; i < cols; i++){
        for (int j = 0; j < rows; j++){
            img.at<uchar>(i, j) = int(m_map[i * cols + j]);
        }
    }

    // Mat to Vector2int
    vector<vector <int>> grid(m_mx, vector<int>(m_my));
    for (int i = 0; i < m_mx; i++){
        for (int j = 0; j < m_my; j++){
            // 1 is reachable
            // 0 is blocked
            if (int(img.at<uchar>(i, j)) == 0){
                grid[i][j] = 1;
                vecGrid[i][j] = 1;
            }
            if (int(img.at<uchar>(i, j)) == 1){
                grid[i][j] = 0;
                vecGrid[i][j] = 0;
            }
        }
    }

    return grid;
}

Mat AStar::vec2RawMap() {
    Mat img;
    img = Mat(ROW, COL, CV_8U, Scalar::all(255));
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            if (vecGrid[i][j] == 1) continue;
            if (vecGrid[i][i] == 0){
                img.at<uchar>(i, j) = 0;
            }
        }
    }
    return img;
}

Vec2int AStar::getBoundaryGrid(Vec2int &raw) const{
    Mat mat;
    Vec2int boundaryGrid;
    mat = Mat(ROW, COL, CV_8U, Scalar::all(255));
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            mat.at<uchar>(i, j) = raw[i][j];
        }
    }

    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    erode(mat, mat, element);

    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            boundaryGrid[i][j] = int(mat.at<uchar>(i, j));
        }
    }

    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            cout << boundaryGrid[i][j];
        }
        cout << endl;
    }

    return boundaryGrid;
}


