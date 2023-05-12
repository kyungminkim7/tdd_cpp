#include <gmock/gmock.h>

#include <memory>

using namespace ::testing;

class Http {
public:
    virtual ~Http() = default;
    virtual void initialize() = 0;
    virtual std::string get(const std::string &url) const = 0;
};

class HttpStub : public Http {
public:
    MOCK_METHOD(void, initialize, (), (override));
    MOCK_METHOD(std::string, get, (const std::string &url), (const, override));
};

class PlaceDescriptionService {
private:
    using HttpPtr = std::unique_ptr<Http>;

public:
    explicit PlaceDescriptionService(HttpPtr http) : http(std::move(http)) {}

    std::string summaryDescription(const std::string &latitude, const std::string &longitude) {
        const std::string server = "http://open.mapquestapi.com/";
        const std::string document = "nominatim/v1/reverse";
        const std::string url = server + document + "?" +
            keyValue("format", "json") + "&" +
            keyValue("lat", latitude) + "&" +
            keyValue("lon", longitude);

        http->get(url);

        return "";
    }

private:
    std::string keyValue(const std::string &key, const std::string &value) const {
        return key + "=" + value;
    }

    HttpPtr http;
};

class APlaceDescriptionService : public Test {
public:
    std::string validLatitude = "MyLat";
    std::string validLongitude = "MyLon";
};

TEST_F(APlaceDescriptionService, MakesHttpRequestToObtainAddress) {
    const std::string urlStart = "http://open.mapquestapi.com/nominatim/v1/reverse?format=json&";
    const auto expectedUrl = urlStart + 
        "lat=" + validLatitude +  "&"
        "lon=" + validLongitude;
    auto httpStub = std::make_unique<HttpStub>();
    EXPECT_CALL(*httpStub, get(expectedUrl));

    PlaceDescriptionService service(std::move(httpStub));

    service.summaryDescription(validLatitude, validLongitude);
}