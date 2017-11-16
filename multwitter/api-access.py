from twython import Twython
import json


with open('secret.json', 'r') as f:
    data = json.load(f)

twitter = Twython(data['APP_KEY'], data['APP_SECRET'])
auth = twitter.get_authentication_tokens()

results = twitter.cursor(twitter.search, q='Python')
# print(len(results))
# for result in results:
#     print(result['user'])
count = 0
for result in results:
    count += 1
    print(count)
