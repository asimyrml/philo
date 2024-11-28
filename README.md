# Yemekteki Filozoflar Problemi (Dining Philosophers Problem)

Bir masa hayal et; bu masanın etrafında **N** filozof oturuyor ve her filozof, sırasıyla şu üç eylemi gerçekleştiriyor: **Düşünme**, **Yeme**, **Uyuma**. Ancak bu filozofların yemek yiyebilmesi için çatallara ihtiyacı var ve her biri yemek için iki çatal kullanmak zorunda. Filozofların nasıl davrandığını daha iyi anlamak için şu adımlara bakalım:

## Masa Düzeni
Masanın etrafında oturan filozoflar var ve her filozofun sağında ve solunda bir çatal var. 
- Örneğin, 5 filozof varsa, 5 çatal vardır ve bu çatallar filozoflar arasında paylaşılıyor.
- Her filozof sağ ve solundaki çatalı alarak yemek yemeye çalışır. Bu çatal alma durumu eş zamanlılık ve senkronizasyon sorunlarına yol açabilir.

![image](https://github.com/user-attachments/assets/666cd332-60ed-4615-9526-a6e12f00ba87)

### Filozofların Masaya Oturması
Her filozof, yuvarlak bir masa etrafında oturuyor. Filozofların aralarına yerleştirilmiş çatallar var.
- Örneğin, 5 filozof var ise ve onları **F1**, **F2**, **F3**, **F4**, **F5** olarak isimlendirirsek, aralarına **C1**, **C2**, **C3**, **C4**, **C5** şeklinde 5 çatal yerleştirilmiştir.

### Filozofların Eylemleri
Her filozof, şu üç durumda olabilir: **Düşünme**, **Yeme**, veya **Uyuma**.
- Filozoflar yemek yiyebilmek için hem sağındaki hem de solundaki çatalı almak zorundadır.
- Ancak aynı anda iki filozof yanlarındaki aynı çatalı almaya çalıştığında bir çakışma (**race condition**) oluşabilir.

### Çatal Kullanımı
- Her filozofun solunda ve sağında birer çatal vardır. Bu nedenle, bir filozof yemek yemek için önce solundaki çatalı, sonra sağındaki çatalı alır.
- Eğer sadece bir çatal mevcutsa, filozof yemek yiyemez ve diğer çatalın serbest bırakılmasını bekler.

## Nasıl İşler?
Filozofların yemek yeme sırasındaki mantığı ve bu süreçte oluşabilecek sorunları adım adım anlatalım:

### 1. Düşünme
Filozoflar yemek yemeden önce bir süre düşünürler. Bu **düşünme** süreci, onların yemeye başlamadan önce bekleme süresidir. Yani her filozof "Düşünüyorum" diyerek belirli bir süre bekler.

### 2. Yemek Yeme Süreci
- Filozoflar yemek yemek için iki çatal almak zorundadır. Her filozof önce solundaki çatalı, ardından sağındaki çatalı alır.
- Eğer her iki çatal da müsaitse, filozof yemek yer. Ancak bazen bir çatal müsaitken diğeri değildir ve bu durumda beklemek zorunda kalır.

### 3. Çatal Paylaşımı
- Örneğin, **F1** filozofu, **C1** ve **C5** çatallarını kullanmalıdır. Eğer **C5** çatalı, **F5** tarafından kullanılıyorsa, **F1** beklemek zorundadır.
- Bu durum her filozof için geçerlidir. Yani herkesin hem sağındaki hem solundaki çatalı alması gerektiğinden, çatal paylaşımı büyük bir sorun haline gelir.

### 4. Uyuma
- Yemek yiyen filozof, çatalları yerine bıraktıktan sonra bir süre **uyur**. Bu da filozofların belli bir süre yemek yemedikten sonra dinlenme sürecidir.
- Uyumak, diğer filozofların yemek yiyebilmesi için çatal paylaşımını sağlar.

## Problemin Zorlukları
Bu problemde bazı klasik zorluklar vardır:

### 1. Deadlock (Kilitlenme)
- Eğer her filozof aynı anda solundaki çatala ulaşırsa ve sonra sağındaki çatalı almak için beklerse, her filozof bir çatalı elinde tutar ve diğer çatalı bekler. Bu durumda kimse yemek yiyemez ve bir **deadlock** oluşur.
- Bu durumu engellemek için bazı stratejiler uygulanır. Örneğin, bazı filozoflara sol çatala ulaşmadan önce kısa süreli bir uyuma emri vermek gibi.

### 2. Aç Kalma (Starvation)
- Eğer bir filozof sürekli olarak çatalları alamazsa, bu filozof **aç kalabilir** ve program onun yemek yiyemeden ölmesine sebep olabilir. Bu durumu engellemek için her filozofun belirli bir süre içinde yemek yemesi sağlanır.

## Mutex Kullanımıyla Çözüm
Bu problemde **mutex** kullanılarak çatalların senkronize bir şekilde kullanılması sağlanır:

- **Mutexler**, aynı anda yalnızca bir thread’in belirli bir kaynağa erişmesine izin verir. Bu durumda her çatal, bir **mutex** ile korunur.
- Filozof bir çatalı almak istediğinde, mutex'i kilitler (`pthread_mutex_lock`). Bu sayede o çatal başka bir filozof tarafından alınamaz.
- Yemek yedikten sonra çatal bırakılır (`pthread_mutex_unlock`) ve diğer filozofların kullanımı için serbest bırakılır.

## Kodla İlişkisi
Senin paylaştığın kodda da benzer bir mantık var:

- **Thread'ler**: Her filozof bir thread olarak oluşturuluyor. `pthread_create()` fonksiyonuyla başlatılıyorlar ve her biri bağımsız bir şekilde çalışıyor.
- **Mutexler**: `pthread_mutex_lock()` ve `pthread_mutex_unlock()` kullanılarak çatalların senkronizasyonu sağlanıyor. Bu sayede, bir çatal birden fazla filozof tarafından aynı anda kullanılamıyor.
- **Ölüm ve Durma Durumu**: Eğer bir filozof belirli bir süre boyunca yemek yiyemezse, bu filozof **ölür** ve program sona erer.

## Özet
"Yemekteki Filozoflar" problemi, kaynakların adil ve eşzamanlı paylaşımını çözmeye yönelik bir modeldir. Bu problemde:

- Her filozof, yemek yiyebilmek için iki çatal almak zorundadır.
- Bu çatalların paylaşımı **mutex** kullanılarak senkronize edilir.
- **Deadlock** ve **starvation** gibi durumları önlemek için farklı stratejiler uygulanır.

Bu problem, senkronizasyon ve eşzamanlılık konularını anlamak için çok önemli bir çalışma alanı sunar.
