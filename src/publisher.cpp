#include <iostream>
#include <vector>
#include <hiredis/hiredis.h>
#include <string>

int main() {
    // Connect to Redis
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        if (c) {
            std::cout << "Error: " << c->errstr << std::endl;
            redisFree(c);
        } else {
            std::cout << "Can't allocate redis context" << std::endl;
        }
        return 1;
    }
    std::cout << "Connected to Redis server" << std::endl;

    std::vector<std::string> channels = {"channel1", "channel2", "channel3"};


    std::string dbFileName = "test.db";
    std::string sqlStructure = "CREATE TABLE IF NOT EXISTS my_table (id INT, name TEXT);";

    for (const auto& channel : channels) {
        std::string createMessage = "CREATE " + dbFileName + " \"" + sqlStructure + "\"";
        redisReply *reply = (redisReply *)redisCommand(c, "PUBLISH %s %s", channel.c_str(), createMessage.c_str());
        if (reply == NULL) {
            std::cout << "Error publishing message to " << channel << std::endl;
        } else {
            std::cout << "Published CREATE message to " << channel << std::endl;
            freeReplyObject(reply);
        }
    }


    std::string dataToInsert = "1, 'Jitanshu raut'";

    for (const auto& channel : channels) {
        std::string insertMessage = "INSERT " + dbFileName + " \"" + dataToInsert + "\"";
        redisReply *reply = (redisReply *)redisCommand(c, "PUBLISH %s %s", channel.c_str(), insertMessage.c_str());
        if (reply == NULL) {
            std::cout << "Error publishing message to " << channel << std::endl;
        } else {
            std::cout << "Published INSERT message to " << channel << std::endl;
            freeReplyObject(reply);
        }
    }

    redisFree(c);
    return 0;
}
