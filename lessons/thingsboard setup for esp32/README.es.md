# Pasos para configurar ThingsBoard y programar el ESP32

[![en](https://img.shields.io/badge/lang-en-red.svg)](https://github.com/Smart-Blueprints/esp32-and-thingsboard-setup-guide/blob/main/lessons/thingsboard%20setup%20for%20esp32/README.md)
[![es](https://img.shields.io/badge/lang-es-yellow.svg)](https://github.com/Smart-Blueprints/esp32-and-thingsboard-setup-guide/blob/main/lessons/thingsboard%20setup%20for%20esp32/README.es.md)

## 1. Crear una cuenta gratuita en ThingsBoard

- **Crear un correo temporal**:
  
  Visita [Temp-Mail](https://temp-mail.org/es/).
  
  Copia la dirección de correo desechable proporcionada al abrir la página.
  
  ![Crear correo temporal](images/creating-temporary-email.png)

- **Registrar una cuenta en ThingsBoard Cloud**:
  
  Ve a la [página de registro de ThingsBoard Cloud](https://thingsboard.cloud/signup).
  
  Completa los datos requeridos para crear una cuenta.

  ![Crear cuenta en ThingsBoard](images/create-thingboard-account.png)

- **Verificar tu correo electrónico**:
  
  Revisa el correo de verificación enviado a la dirección de correo temporal.
  
  ![Verificar correo electrónico](images/verify-email.png)

  Haz clic en el botón "Activar tu cuenta".
  
  ![Activar cuenta en ThingsBoard](images/activate-thingsboard-account.png)

- **Inicia sesión en ThingsBoard**:
  
  Después de la activación, haz clic en el botón "Login" para acceder a tu cuenta de ThingsBoard.

---

## 2. Configurar la cuenta de ThingsBoard
- **Crear un dispositivo**:
  
  Navega a **Entities > Devices**.
  
  ![Panel de entidades en ThingsBoard](images/thingsboard-entities-panel.png)

  Crea un nuevo dispositivo que representará el hogar inteligente.
  
  ![Crear un nuevo dispositivo](images/create-new-device.png)

  Asigna un nombre al dispositivo y haz clic en **Add**.
  
  ![Nombrar el dispositivo](images/naming-the-new-device.png)

  Cierra la ventana emergente, haz clic en el dispositivo recién creado y copia el **token de acceso** para vincularlo con tu programa.
  
  ![Copiar el token de acceso](images/copy-access-token.png)

- **Configurar el tablero (Dashboard)**:
  
  Ve a la sección **Dashboards**.
  
  ![Panel de dashboard](images/dashboard-panel.png)

  Importa un tablero preconfigurado para visualizar parámetros y controlar el hogar inteligente:
  
  ![Importar dashboard](images/import-dashboard.png)
  
  Arrastra y suelta el archivo `smarthome.json` (proporcionado en la carpeta de la clase) en el área indicada.
  
  Haz clic en el botón **Import**.
  
  ![Arrastrar y soltar archivo de configuración](images/drag-and-drop-config-file.png)

  Abre el tablero recién importado (nota: es posible que los datos no se muestren inicialmente).
  
  ![Abrir dashboard importado](images/open-imported-dashboard.png)

  Entra en el **modo de edición** del tablero.
  
  ![Modo de edición del tablero](images/dashboard-edit-mode.png)

  Para cada widget, accede a su **editor de propiedades**:
  
  ![Editor de propiedades](images/property-editor.png)

  Vincula el widget al dispositivo creado anteriormente.
  
  ![Vincular widget al dispositivo](images/link-widget-to-device.png)

  Repite este proceso para todos los widgets.
  
  Una vez que todos los widgets estén vinculados al dispositivo, haz clic en **Save**.
  
  ![Guardar dispositivos vinculados](images/save-linked-devices.png)

---

## 3. Programar el ESP32 para conectarse a ThingsBoard
- **Crear un punto de acceso WiFi**:
  
  Usa un teléfono móvil con conexión a internet estable para crear un punto de acceso WiFi.
  
  El ESP32 se conectará a este punto de acceso para comunicarse con ThingsBoard.

- **Abrir el código del proyecto**:
  
  Ubica el código `smart-home-project-TB.ino` proporcionado en la carpeta de la clase.
  
  Modifica las siguientes líneas en el código:
  
  Reemplaza el nombre y la contraseña del WiFi con los detalles del punto de acceso que creaste.
  
  ![Actualizar nombre y contraseña de WiFi](images/update-wifi-and-password.png)

  Actualiza el **token de acceso** con el token del dispositivo creado en ThingsBoard.
    
  ![Actualizar token de acceso](images/update-access-token.png)

- **Visualizar los datos en el tablero**:
  
  Abre el tablero configurado en ThingsBoard para monitorear los parámetros del hogar y controlarlo.
