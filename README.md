# computer_organization_final_pj

- 硬體: MacbookPro 2020 i5-core
- virtual machine: UTM
- 虛擬機環境: Ubuntu 22.04
  - memory: 4096
  - CPU num: default

## 執行
我是跑 Ubuntu 18.04 container

```
docker contianer ls -a
```
```
docker start ubuntu18.04-container
```
```
docker exec -it ubuntu18.04-container /bin/bash
```

## 簡介
Gem5 模擬電腦硬體全系統架構，但主要還是圍繞在 CPU(如下圖)，而 NVMain 是針對 Non-Volatile Memories 的模擬器，搭配兩者可以模擬出更完整的電腦架構。不過 Gem5 為了讓我們更清楚內部運作，由程式碼來取代硬體的呈現，因此在修改完成後要把整個 gem5 重新編譯一次，才能算是設定好整個「電腦硬體」，也就是 gem5.opt 這個檔案。

![image](https://github.com/ki225/computer_organization_final_pj/assets/123147937/bd970da7-8cc8-488f-ad82-5b39d66f3f0a)

![image](https://github.com/ki225/computer_organization_final_pj/assets/123147937/4c337075-957a-404b-a38a-ba63f4aebebc)

Gem5 是事件驅動，傳遞的單位是 packet，在 gem/src/mem/cache/ 裡的某些檔案(應該是修改 LFU 的 cc 檔案那邊)可以看到 packet_ptr 等等的資料名稱。

![image](https://github.com/ki225/computer_organization_final_pj/assets/123147937/aaeb1c96-3d0d-4608-8712-cadd81af43d9)


![image](https://github.com/ki225/computer_organization_final_pj/assets/123147937/d0815bf2-aa70-4ae9-a728-7e1ad7d8de9b)


- [ref](https://skywf.blog.csdn.net/article/details/104628839?spm=1001.2101.3001.6650.1&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-104628839-blog-80803833.235%5Ev43%5Econtrol&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-1-104628839-blog-80803833.235%5Ev43%5Econtrol&utm_relevant_index=2&ydreferer=aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzE3NjE0Mjk3L2FydGljbGUvZGV0YWlscy84MDgwMzgzMw%3D%3D)

- [ref](https://blog.csdn.net/qq_46675545/article/details/128103618)
