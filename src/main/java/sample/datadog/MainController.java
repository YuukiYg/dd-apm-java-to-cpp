package sample.datadog;

import java.time.LocalDateTime;

import org.springframework.beans.factory.InitializingBean;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import datadog.trace.api.Trace;
import io.micrometer.core.annotation.Timed;
import jnr.ffi.LibraryLoader;
import lombok.extern.slf4j.Slf4j;

@RestController
@Slf4j
@Timed
public class MainController implements InitializingBean {
	private INative iNative;

	/**
	 *
	 * @return
	 */
	@RequestMapping(value = "/test", method = RequestMethod.GET)
	@Timed(value = "time.logging.callnative")
	@Trace(operationName = "trace.logging.callnative", resourceName = "MainController.loggingWithNative")
	public String loggingWithNative() {

		log.info("CALLING C++ from Java >>>>>>>>>>");
		int cppResult = iNative.plus(2, 4); // Calling C++ module here.
		assert cppResult == 6;
		log.info("<<<<<<<<<< C++ FINISHED. Result={}", cppResult);

		return "finished. " + LocalDateTime.now().toString();
	}

	@Override
	public void afterPropertiesSet() throws Exception {
		// a file named "libplus.{dll, dylib, so}" should be set on the path "-Djava.library.path".
		this.iNative = LibraryLoader.create(INative.class).load("plus");
	}
}
