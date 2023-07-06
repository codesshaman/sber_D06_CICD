#!/bin/bash
URL="https://api.telegram.org/bot5651628231:AAHYEIg5pUKdR8z6a_umayILjSpEnGLxiGw/sendMessage"
TEXT="CI/CD STATUS: $1%0A%0AProject:+$CI_PROJECT_NAME%0AStatus:+$CI_JOB_STATUS%0AURL:+$CI_PROJECT_URL/pipelines/$CI_PIPELINE_ID/%0ABranch:+$CI_COMMIT_REF_SLUG"

curl -s -d "chat_id=689680786&web_page_preview=1&text=$TEXT" $URL > /dev/null
