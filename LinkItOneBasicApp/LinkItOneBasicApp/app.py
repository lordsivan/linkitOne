import sys
import endpoints
from protorpc import messages
from protorpc import message_types
from protorpc import remote
from email import email


from google.appengine.ext.endpoints import api_config
AUTH_CONFIG = api_config.ApiAuth(allow_cookie_auth=True)
   
APPLICATION = endpoints.api_server([],restricted=False)
