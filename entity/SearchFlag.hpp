//标志MySQL查找结果的状态
enum SearchFlag{
    NONE, //没找到
    FIND, //找到了
    SQLERROR //查询数据库发生异常
};