### Part 1. Настройка **gitlab-runner**

1.1 Установка gitlab-runner  

Download 
> curl -LJO "https://gitlab-runner-downloads.s3.amazonaws.com/latest/deb/gitlab-runner_amd64.deb"  

Install:
> dpkg -i gitlab-runner_amd64.deb  

![./screenshots/1.png](./screenshots/1.png)  
![./screenshots/2.png](./screenshots/2.png)  

1.2 Регистрация раннера в gitlab-runner  

> sudo gitlab-runner register  

Добавляем раннеру те теги, что будут использоваться в gitlab-ci.yml (так он сможет приступить к job`е)
![./screenshots/3.png](./screenshots/3.png)
Валидируем раннеров    
> sudo gitlab-runner verify  

Проверяем статус службы "gitlab-runner"
> service gitlab-runner status


## Part 2. Сборка

2.1 Создание и конфигурация .gitlab-ci.yml в корне репозитория
> vim .gitlab-ci.yml  
  
![./screenshots/4.png](./screenshots/4.png)   
Запуск пайп-лайна, запуск раннера
> sudo gitlab-runner run    
  
Раннер успешно выполнил job по сборке проекта
![./screenshots/5.png](./screenshots/5.png)    


### Part 3. Тест кодстайла

3.1 Добавляем stage для кодстайла в gitlab-ci.yml и пушим в репозиторий.  
![./screenshots/6.png](./screenshots/6.png)    

Проверяем результат работы раннера, как видим - кодстайл не прошёл и зафейлил пайплайн
![./screenshots/7.png](./screenshots/7.png)    
![./screenshots/8.png](./screenshots/8.png)  

Исправляем кодстайл, запускаем проверку вновь.
Кодстайл прошёл успешно, пайплайн завершен.
![./screenshots/9.png](./screenshots/9.png)    
![./screenshots/10.png](./screenshots/10.png)  


### Part 4. Интеграционные тесты

4.1 Добавляет test в gitlab-ci.yml, пушим в репозиторий.  
![./screenshots/11.png](./screenshots/11.png)   

Проверяем результат работы раннера, тест прошёл, пайплайн завершён.
![./screenshots/12.png](./screenshots/12.png)  
![./screenshots/13.png](./screenshots/13.png)  

Попробуем намеренно зафейлить тесты, пайплайн должен прерваться.  
![./screenshots/14.png](./screenshots/14.png)  
![./screenshots/15.png](./screenshots/15.png)  


### Part 5. Этап деплоя

5.1 Клонируем машину  
![./screenshots/16.png](./screenshots/16.png)  

5.2 Изменяем файл /etc/netplan/00-installer-config.yaml на обеих машинах:
![./screenshots/17.png](./screenshots/17.png)  

5.3 Изменяем параметры сетевого адаптера на обеих машинах:
![./screenshots/18.png](./screenshots/18.png)   
ping идёт:  
![./screenshots/19.png](./screenshots/19.png)  

5.4 Добавляем этап деплоя в gitlab-ci.yml  
![./screenshots/20.png](./screenshots/20.png)   

5.5 Создаём скрипт copy.sh, который будет передавать файлы через ssh, с помощью утилиты scp (копирование файлов через ssh)
![./screenshots/21.png](./screenshots/21.png)  

5.6 Создадим пользователя gitlab-runner ```sudo su - gitlab-runner```, сгенерируем и скопируем его ssh на вторую машину  
![./screenshots/22.png](./screenshots/22.png)   
> ssh-keygen -t rsa -b 2045  
> ssh-copy-id milagros@10.10.0.2  

![./screenshots/23.png](./screenshots/23.png)   

5.7 Выдадим права на второй машине, для папки `/usr/local/bin/`
> sudo chmod -R 777 /usr/local/bin  

![./screenshots/24.png](./screenshots/24.png)   

5.8 Пушим измененный yml и скрипт copy.sh, пайплайн проходит и ожидает ручного запуска:  
![./screenshots/25.png](./screenshots/25.png) 

5.9 Деплой прошёл успешно, файлы появились в нужной папке на второй машине:  
![./screenshots/26.png](./screenshots/26.png) 


## Part 6. Дополнительно. Уведомления  

6.1 Напишем @botfather, чтобы создать бота и получить его токен:
![./screenshots/28.png](./screenshots/28.png)   

6.2 Добавим по вызову скрипта `notify.sh` после каждой стадии в .yml:  
![./screenshots/29.png](./screenshots/29.png) 

6.3 Содержимое скрипта `notify.sh`:  
![./screenshots/30.png](./screenshots/30.png)  

6.4 Оповещения от бота приходят после каждой стадии пайплайна:  
![./screenshots/27.png](./screenshots/27.png) 


extra:  
first machine dump - https://drive.google.com/file/d/172Y-IV5ITtNaL0G_Qy9MKama8G-9hVRC/view?usp=share_link  
second machine dump - https://drive.google.com/file/d/1cVwWo5KIMXS95TuwZJd2rPFbrKXUmwtv/view?usp=sharing
