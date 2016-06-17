#!/bin/bash

# Fill out the username and api_key
if grep -q LASTFMUSER lastfm_hook.json
then
  read -p 'Last.fm user: ' user
fi

if grep -q LASTFMAPIKEY lastfm_hook.json
then
  read -p 'Last.fm api key: ' api_key
fi

sed -i -e "s/LASTFMUSER/${user}/" -e "s/LASTFMAPIKEY/${api_key}/" lastfm_hook.json

particle webhook create lastfm_hook.json
