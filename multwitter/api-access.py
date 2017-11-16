from twython import Twython
import json


with open('secret.json') as f:
    data = json.load(f)

twitter = Twython(data['APP_KEY'], data['APP_SECRET'])

auth = twitter.get_authentication_tokens()
