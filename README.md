# CH9141

Este es un IC que permite la comunicación Bluetooth a través de la comunicación serial de forma transparente. Lo impresionante de este chip es su simplicidad de conexión electrónica con apenas cuatro componentes y su simple configuración mediante comandos AT. Es diseñado y fabricado en china por [Jiangsu Heng Qin Ltd. (WCH)](http://www.wch-ic.com).

Existen diferentes formas de conectar el Bluetooth, en este repositorio nos centraremos en cómo se indica en el siguiente diagrama, para conocer más formas de conexión vea él [datasheet](https://github.com/nstrappazzonc/CH9141/blob/main/doc/CH9141DS1.PDF).

![](https://github.com/nstrappazzonc/CH9141/blob/main/img/overview.png?raw=true)

Podrá usar el IC para conectarse directamente a un PC o móvil, vea los siguientes [ejemplos](https://github.com/openwch/ch9141).

Puedes conseguir los IC o una placa de pruebas en la tienda oficial de [AliExpress](https://wchofficialstore.es.aliexpress.com/store/1100367542) o en [JLCMC](https://jlcmc.com).

De momento nos vamos a centrar en él [CH9141K](https://www.wch-ic.com/products/CH9141.html) que tiene unas prestaciones muy versátiles, entre ellas destacan las siguientes:

- Soporta el estándar Bluetooth BLE4.2 que es de bajo consumo.
- Llega hasta 100 metros de distancia.
- Soporta la configuración mediante comandos AT.
- Soporta diferentes modos: broadcast, host y slave.
- Permite una comunicación asíncrona de hasta 5Mbps.

## Componentes

Use los siguientes componentes para construir el circuito mínimo:

- Un IC CH9141K.
- Oscilador externo de 32MHz 10PPM y 12pF.
- Dos capacitores 2.2 uF.
